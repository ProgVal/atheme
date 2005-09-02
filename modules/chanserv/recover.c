/*
 * Copyright (c) 2005 William Pitcock, et al.
 * Rights to this code are as documented in doc/LICENSE.
 *
 * This file contains code for the CService RECOVER functions.
 *
 * $Id: recover.c 1983 2005-09-01 03:14:44Z nenolod $
 */

#include "atheme.h"

DECLARE_MODULE_V1("chanserv/recover", FALSE, _modinit, _moddeinit);

static void cs_cmd_recover(char *origin);

command_t cs_recover = { "RECOVER", "Regain control of your channel.",
                        AC_NONE, cs_cmd_recover };

list_t *cs_cmdtree;

void _modinit(module_t *m)
{
	cs_cmdtree = module_locate_symbol("chanserv/main", "cs_cmdtree");
        command_add(&cs_recover, cs_cmdtree);
}

void _moddeinit()
{
	command_delete(&cs_recover, cs_cmdtree);
}

static void cs_cmd_recover(char *origin)
{
	user_t *u = user_find(origin);
	chanuser_t *cu;
	mychan_t *mc;
	node_t *n;
	char *name = strtok(NULL, " ");
	char hostbuf[BUFSIZE];

	if (!name)
	{
		notice(chansvs.nick, origin, "Insufficient parameters specified for \2RECOVER\2.");
		notice(chansvs.nick, origin, "Syntax: RECOVER <#channel>");
		return;
	}

	if (!u->myuser)
	{
		notice(chansvs.nick, origin, "You are not logged in.");
		return;
	}

	if (!(mc = mychan_find(name)))
	{
		notice(chansvs.nick, origin, "\2%s\2 is not registered.", name);
		return;
	}

	if (!is_xop(mc, u->myuser, CA_RECOVER))
	{
		notice(chansvs.nick, origin, "You are not authorized to perform this operation.");
		return;
	}

	verbose(mc, "\2%s\2 used RECOVER.", origin);

	/* deop everyone */
	LIST_FOREACH(n, mc->chan->members.head)
	{
		cu = (chanuser_t *)n->data;

		if ((CMODE_OP & cu->modes) && (irccasecmp(chansvs.nick, cu->user->nick)))
		{
			cmode(chansvs.nick, mc->chan->name, "-o", CLIENT_NAME(cu->user));
			cu->modes &= ~CMODE_OP;
		}
	}

	/* remove modes that keep people out */
	if (CMODE_LIMIT & mc->chan->modes)
	{
		cmode(chansvs.nick, mc->chan->name, "-l", NULL);
		mc->chan->modes &= ~CMODE_LIMIT;
		mc->chan->limit = 0;
	}

	if (CMODE_INVITE & mc->chan->modes)
	{
		cmode(chansvs.nick, mc->chan->name, "-i", NULL);
		mc->chan->modes &= ~CMODE_INVITE;
	}

	if (CMODE_KEY & mc->chan->modes)
	{
		cmode(chansvs.nick, mc->chan->name, "-k", mc->chan->key);
		mc->chan->modes &= ~CMODE_KEY;
		free(mc->chan->key);
		mc->chan->key = NULL;
	}

	/* set an exempt on the user calling this */
	hostbuf[0] = '\0';

	strlcat(hostbuf, u->nick, BUFSIZE);
	strlcat(hostbuf, "!", BUFSIZE);
	strlcat(hostbuf, u->user, BUFSIZE);
	strlcat(hostbuf, "@", BUFSIZE);
	strlcat(hostbuf, u->vhost, BUFSIZE);

	/* no exception list structure right now */
	/* XXX check to see if the ircd even does +e */
	cmode(chansvs.nick, mc->chan->name, "+e", hostbuf);

	/* invite them back. */
	/* XXX need to wrap this, same with CS INVITE */
	sts(":%s INVITE %s %s", chansvs.nick, u->nick, mc->chan->name);

	notice(chansvs.nick, origin, "Recover complete for \2%s\2.", mc->chan->name);
}
