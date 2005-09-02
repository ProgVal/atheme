/*
 * Copyright (c) 2005 Atheme Development Group
 * Rights to this code are as documented in doc/LICENSE.
 *
 * Uplink management stuff.
 *
 * $Id: uplink.c 1139 2005-07-25 09:56:03Z nenolod $
 */

#include "atheme.h"

uplink_t *curr_uplink;

void uplink_connect(void)
{
	uplink_t *u;

	if (curr_uplink == NULL)
	{
		slog(LG_DEBUG, "uplink_connect(): connecting to first entry.");
		curr_uplink = uplinks.head->data;
	}
	else if (curr_uplink->node->next)
	{
		u = curr_uplink->node->next->data;

		if (u == uplinks.tail->data)
			u = uplinks.head->data;

		slog(LG_DEBUG, "uplink_connect(): trying alternate uplink `%s'",
			u->name);

		curr_uplink = u;
	}

	u = curr_uplink;

	curr_uplink->conn = connection_open_tcp(u->host, me.vhost, u->port, irc_rhandler, sendq_flush);
}
