/*******************************************************************************

  Copyright(c) 2004 Intel Corporation. All rights reserved.

  Portions of this file are based on the WEP enablement code provided by the
  Host AP project hostap-drivers v0.1.3
  Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
  <jkmaline@cc.hut.fi>
  Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  The full GNU General Public License is included in this distribution in the
  file called LICENSE.

  Contact Information:
  James P. Ketrenos <ipw2100-admin@linux.intel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

*******************************************************************************/

#include <linux/compiler.h>
#include <linux/config.h>
#include <linux/errno.h>
#include <linux/if_arp.h>
#include <linux/in6.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/proc_fs.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/tcp.h>
#include <linux/types.h>
#include <linux/version.h>
#include <linux/wireless.h>
#include <linux/etherdevice.h>
#include <asm/uaccess.h>
#include <net/arp.h>

#include <net/ieee80211.h>

MODULE_DESCRIPTION("802.11 data/management/control stack");
MODULE_AUTHOR
    ("Copyright (C) 2004 Intel Corporation <jketreno@linux.intel.com>");
MODULE_LICENSE("GPL");

#define DRV_NAME "ieee80211"

static inline int ieee80211_networks_allocate(struct ieee80211_device *ieee)
{
	if (ieee->networks)
		return 0;

	ieee->networks =
	    kmalloc(MAX_NETWORK_COUNT * sizeof(struct ieee80211_network),
		    GFP_KERNEL);
	if (!ieee->networks) {
		printk(KERN_WARNING "%s: Out of memory allocating beacons\n",
		       ieee->dev->name);
		return -ENOMEM;
	}

	memset(ieee->networks, 0,
	       MAX_NETWORK_COUNT * sizeof(struct ieee80211_network));

	return 0;
}

static inline void ieee80211_networks_free(struct ieee80211_device *ieee)
{
	if (!ieee->networks)
		return;
	kfree(ieee->networks);
	ieee->networks = NULL;
}

static inline void ieee80211_networks_initialize(struct ieee80211_device *ieee)
{
	int i;

	INIT_LIST_HEAD(&ieee->network_free_list);
	INIT_LIST_HEAD(&ieee->network_list);
	for (i = 0; i < MAX_NETWORK_COUNT; i++)
		list_add_tail(&ieee->networks[i].list,
			      &ieee->network_free_list);
}

struct net_device *alloc_ieee80211(int sizeof_priv)
{
	struct ieee80211_device *ieee;
	struct net_device *dev;
	int err;

	IEEE80211_DEBUG_INFO("Initializing...\n");

	dev = alloc_etherdev(sizeof(struct ieee80211_device) + sizeof_priv);
	if (!dev) {
		IEEE80211_ERROR("Unable to network device.\n");
		goto failed;
	}
	ieee = netdev_priv(dev);
	dev->hard_start_xmit = ieee80211_xmit;

	ieee->dev = dev;

	err = ieee80211_networks_allocate(ieee);
	if (err) {
		IEEE80211_ERROR("Unable to allocate beacon storage: %d\n", err);
		goto failed;
	}
	ieee80211_networks_initialize(ieee);

	/* Default fragmentation threshold is maximum payload size */
	ieee->fts = DEFAULT_FTS;
	ieee->scan_age = DEFAULT_MAX_SCAN_AGE;
	ieee->open_wep = 1;

	/* Default to enabling full open WEP with host based encrypt/decrypt */
	ieee->host_encrypt = 1;
	ieee->host_decrypt = 1;
	ieee->ieee802_1x = 1;	/* Default to supporting 802.1x */

	INIT_LIST_HEAD(&ieee->crypt_deinit_list);
	init_timer(&ieee->crypt_deinit_timer);
	ieee->crypt_deinit_timer.data = (unsigned long)ieee;
	ieee->crypt_deinit_timer.function = ieee80211_crypt_deinit_handler;

	spin_lock_init(&ieee->lock);

	ieee->wpa_enabled = 0;
	ieee->tkip_countermeasures = 0;
	ieee->drop_unencrypted = 0;
	ieee->privacy_invoked = 0;
	ieee->ieee802_1x = 1;

	return dev;

      failed:
	if (dev)
		free_netdev(dev);
	return NULL;
}

void free_ieee80211(struct net_device *dev)
{
	struct ieee80211_device *ieee = netdev_priv(dev);

	int i;

	del_timer_sync(&ieee->crypt_deinit_timer);
	ieee80211_crypt_deinit_entries(ieee, 1);

	for (i = 0; i < WEP_KEYS; i++) {
		struct ieee80211_crypt_data *crypt = ieee->crypt[i];
		if (crypt) {
			if (crypt->ops) {
				crypt->ops->deinit(crypt->priv);
				module_put(crypt->ops->owner);
			}
			kfree(crypt);
			ieee->crypt[i] = NULL;
		}
	}

	ieee80211_networks_free(ieee);
	free_netdev(dev);
}

#ifdef CONFIG_IEEE80211_DEBUG

static int debug = 0;
u32 ieee80211_debug_level = 0;
struct proc_dir_entry *ieee80211_proc = NULL;

static int show_debug_level(char *page, char **start, off_t offset,
			    int count, int *eof, void *data)
{
	return snprintf(page, count, "0x%08X\n", ieee80211_debug_level);
}

static int store_debug_level(struct file *file, const char __user * buffer,
			     unsigned long count, void *data)
{
	char buf[] = "0x00000000";
	char *p = (char *)buf;
	unsigned long val;

	if (count > sizeof(buf) - 1)
		count = sizeof(buf) - 1;

	if (copy_from_user(buf, buffer, count))
		return count;
	buf[count] = 0;
	/*
	 * what a FPOS...  What, sscanf(buf, "%i", &val) would be too
	 * scary?
	 */
	if (p[1] == 'x' || p[1] == 'X' || p[0] == 'x' || p[0] == 'X') {
		p++;
		if (p[0] == 'x' || p[0] == 'X')
			p++;
		val = simple_strtoul(p, &p, 16);
	} else
		val = simple_strtoul(p, &p, 10);
	if (p == buf)
		printk(KERN_INFO DRV_NAME
		       ": %s is not in hex or decimal form.\n", buf);
	else
		ieee80211_debug_level = val;

	return strlen(buf);
}

static int __init ieee80211_init(void)
{
	struct proc_dir_entry *e;

	ieee80211_debug_level = debug;
	ieee80211_proc = proc_mkdir(DRV_NAME, proc_net);
	if (ieee80211_proc == NULL) {
		IEEE80211_ERROR("Unable to create " DRV_NAME
				" proc directory\n");
		return -EIO;
	}
	e = create_proc_entry("debug_level", S_IFREG | S_IRUGO | S_IWUSR,
			      ieee80211_proc);
	if (!e) {
		remove_proc_entry(DRV_NAME, proc_net);
		ieee80211_proc = NULL;
		return -EIO;
	}
	e->read_proc = show_debug_level;
	e->write_proc = store_debug_level;
	e->data = NULL;

	return 0;
}

static void __exit ieee80211_exit(void)
{
	if (ieee80211_proc) {
		remove_proc_entry("debug_level", ieee80211_proc);
		remove_proc_entry(DRV_NAME, proc_net);
		ieee80211_proc = NULL;
	}
}

#include <linux/moduleparam.h>
module_param(debug, int, 0444);
MODULE_PARM_DESC(debug, "debug output mask");

module_exit(ieee80211_exit);
module_init(ieee80211_init);
#endif

const char *escape_essid(const char *essid, u8 essid_len)
{
	static char escaped[IW_ESSID_MAX_SIZE * 2 + 1];
	const char *s = essid;
	char *d = escaped;

	if (ieee80211_is_empty_essid(essid, essid_len)) {
		memcpy(escaped, "<hidden>", sizeof("<hidden>"));
		return escaped;
	}

	essid_len = min(essid_len, (u8) IW_ESSID_MAX_SIZE);
	while (essid_len--) {
		if (*s == '\0') {
			*d++ = '\\';
			*d++ = '0';
			s++;
		} else {
			*d++ = *s++;
		}
	}
	*d = '\0';
	return escaped;
}

EXPORT_SYMBOL(alloc_ieee80211);
EXPORT_SYMBOL(free_ieee80211);
EXPORT_SYMBOL(escape_essid);
