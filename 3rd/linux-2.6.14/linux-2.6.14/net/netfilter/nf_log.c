#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/seq_file.h>
#include <net/protocol.h>

#include "nf_internals.h"

/* Internal logging interface, which relies on the real 
   LOG target modules */

#define NF_LOG_PREFIXLEN		128

static struct nf_logger *nf_logging[NPROTO]; /* = NULL */
static DEFINE_SPINLOCK(nf_log_lock);

/* return EBUSY if somebody else is registered, EEXIST if the same logger
 * is registred, 0 on success. */
int nf_log_register(int pf, struct nf_logger *logger)
{
	int ret = -EBUSY;

	if (pf >= NPROTO)
		return -EINVAL;

	/* Any setup of logging members must be done before
	 * substituting pointer. */
	spin_lock(&nf_log_lock);
	if (!nf_logging[pf]) {
		rcu_assign_pointer(nf_logging[pf], logger);
		ret = 0;
	} else if (nf_logging[pf] == logger)
		ret = -EEXIST;

	spin_unlock(&nf_log_lock);
	return ret;
}		
EXPORT_SYMBOL(nf_log_register);

int nf_log_unregister_pf(int pf)
{
	if (pf >= NPROTO)
		return -EINVAL;

	spin_lock(&nf_log_lock);
	nf_logging[pf] = NULL;
	spin_unlock(&nf_log_lock);

	/* Give time to concurrent readers. */
	synchronize_net();

	return 0;
}
EXPORT_SYMBOL(nf_log_unregister_pf);

void nf_log_unregister_logger(struct nf_logger *logger)
{
	int i;

	spin_lock(&nf_log_lock);
	for (i = 0; i < NPROTO; i++) {
		if (nf_logging[i] == logger)
			nf_logging[i] = NULL;
	}
	spin_unlock(&nf_log_lock);

	synchronize_net();
}
EXPORT_SYMBOL(nf_log_unregister_logger);

void nf_log_packet(int pf,
		   unsigned int hooknum,
		   const struct sk_buff *skb,
		   const struct net_device *in,
		   const struct net_device *out,
		   struct nf_loginfo *loginfo,
		   const char *fmt, ...)
{
	va_list args;
	char prefix[NF_LOG_PREFIXLEN];
	struct nf_logger *logger;
	
	rcu_read_lock();
	logger = rcu_dereference(nf_logging[pf]);
	if (logger) {
		va_start(args, fmt);
		vsnprintf(prefix, sizeof(prefix), fmt, args);
		va_end(args);
		/* We must read logging before nf_logfn[pf] */
		logger->logfn(pf, hooknum, skb, in, out, loginfo, prefix);
	} else if (net_ratelimit()) {
		printk(KERN_WARNING "nf_log_packet: can\'t log since "
		       "no backend logging module loaded in! Please either "
		       "load one, or disable logging explicitly\n");
	}
	rcu_read_unlock();
}
EXPORT_SYMBOL(nf_log_packet);

#ifdef CONFIG_PROC_FS
static void *seq_start(struct seq_file *seq, loff_t *pos)
{
	rcu_read_lock();

	if (*pos >= NPROTO)
		return NULL;

	return pos;
}

static void *seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	(*pos)++;

	if (*pos >= NPROTO)
		return NULL;

	return pos;
}

static void seq_stop(struct seq_file *s, void *v)
{
	rcu_read_unlock();
}

static int seq_show(struct seq_file *s, void *v)
{
	loff_t *pos = v;
	const struct nf_logger *logger;

	logger = rcu_dereference(nf_logging[*pos]);

	if (!logger)
		return seq_printf(s, "%2lld NONE\n", *pos);
	
	return seq_printf(s, "%2lld %s\n", *pos, logger->name);
}

static struct seq_operations nflog_seq_ops = {
	.start	= seq_start,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= seq_show,
};

static int nflog_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &nflog_seq_ops);
}

static struct file_operations nflog_file_ops = {
	.owner	 = THIS_MODULE,
	.open	 = nflog_open,
	.read	 = seq_read,
	.llseek	 = seq_lseek,
	.release = seq_release,
};

#endif /* PROC_FS */


int __init netfilter_log_init(void)
{
#ifdef CONFIG_PROC_FS
	struct proc_dir_entry *pde;

	pde = create_proc_entry("nf_log", S_IRUGO, proc_net_netfilter);
	if (!pde)
		return -1;

	pde->proc_fops = &nflog_file_ops;
#endif
	return 0;
}
