/*
 * linux/net/sunrpc/auth_null.c
 *
 * AUTH_NULL authentication. Really :-)
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#include <linux/types.h>
#include <linux/socket.h>
#include <linux/module.h>
#include <linux/in.h>
#include <linux/utsname.h>
#include <linux/sunrpc/clnt.h>
#include <linux/sched.h>

#ifdef RPC_DEBUG
# define RPCDBG_FACILITY	RPCDBG_AUTH
#endif

static struct rpc_auth null_auth;
static struct rpc_cred null_cred;

static struct rpc_auth *
nul_create(struct rpc_clnt *clnt, rpc_authflavor_t flavor)
{
	atomic_inc(&null_auth.au_count);
	return &null_auth;
}

static void
nul_destroy(struct rpc_auth *auth)
{
}

/*
 * Lookup NULL creds for current process
 */
static struct rpc_cred *
nul_lookup_cred(struct rpc_auth *auth, struct auth_cred *acred, int flags)
{
	return get_rpccred(&null_cred);
}

/*
 * Destroy cred handle.
 */
static void
nul_destroy_cred(struct rpc_cred *cred)
{
}

/*
 * Match cred handle against current process
 */
static int
nul_match(struct auth_cred *acred, struct rpc_cred *cred, int taskflags)
{
	return 1;
}

/*
 * Marshal credential.
 */
static u32 *
nul_marshal(struct rpc_task *task, u32 *p)
{
	*p++ = htonl(RPC_AUTH_NULL);
	*p++ = 0;
	*p++ = htonl(RPC_AUTH_NULL);
	*p++ = 0;

	return p;
}

/*
 * Refresh credential. This is a no-op for AUTH_NULL
 */
static int
nul_refresh(struct rpc_task *task)
{
	task->tk_msg.rpc_cred->cr_flags |= RPCAUTH_CRED_UPTODATE;
	return 0;
}

static u32 *
nul_validate(struct rpc_task *task, u32 *p)
{
	rpc_authflavor_t	flavor;
	u32			size;

	flavor = ntohl(*p++);
	if (flavor != RPC_AUTH_NULL) {
		printk("RPC: bad verf flavor: %u\n", flavor);
		return NULL;
	}

	size = ntohl(*p++);
	if (size != 0) {
		printk("RPC: bad verf size: %u\n", size);
		return NULL;
	}

	return p;
}

struct rpc_authops authnull_ops = {
	.owner		= THIS_MODULE,
	.au_flavor	= RPC_AUTH_NULL,
#ifdef RPC_DEBUG
	.au_name	= "NULL",
#endif
	.create		= nul_create,
	.destroy	= nul_destroy,
	.lookup_cred	= nul_lookup_cred,
};

static
struct rpc_auth null_auth = {
	.au_cslack	= 4,
	.au_rslack	= 2,
	.au_ops		= &authnull_ops,
};

static
struct rpc_credops	null_credops = {
	.cr_name	= "AUTH_NULL",
	.crdestroy	= nul_destroy_cred,
	.crmatch	= nul_match,
	.crmarshal	= nul_marshal,
	.crrefresh	= nul_refresh,
	.crvalidate	= nul_validate,
};

static
struct rpc_cred null_cred = {
	.cr_ops		= &null_credops,
	.cr_count	= ATOMIC_INIT(1),
	.cr_flags	= RPCAUTH_CRED_UPTODATE,
#ifdef RPC_DEBUG
	.cr_magic	= RPCAUTH_CRED_MAGIC,
#endif
};
