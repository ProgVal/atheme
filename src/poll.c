/*
 * Copyright (c) 2005-2006 William Pitcock <nenolod@nenolod.net>
 * Rights to this code are as documented in doc/LICENSE.
 *
 * Socketengine implementing poll().
 *
 * $Id: poll.c 8375 2007-06-03 20:03:26Z pippijn $
 */

#include <sys/poll.h>

#include "atheme.h"
#include "internal.h"
#include "datastream.h"

extern list_t connection_list; /* this lives in connection.c */

/*
 * linux does not provide POLLWRNORM by default, and we're not _XOPEN_SOURCE.
 * so.... we have to do this crap below.
 */
#ifndef POLLRDNORM
#define POLLRDNORM POLLIN
#endif
#ifndef POLLWRNORM
#define POLLWRNORM POLLOUT
#endif

struct pollfd pollfds[FD_SETSIZE]; /* XXX We need a define indicating MAXCONN. */

/*
 * init_socket_queues()
 *
 * inputs:
 *       none
 *
 * outputs:
 *       none
 *
 * side effects:
 *       when using select, we don't need to do anything here.
 */
void init_socket_queues(void)
{
	memset(&pollfds, 0, sizeof(struct pollfd) * FD_SETSIZE);
}

/*
 * update_poll_fds()
 *
 * inputs:
 *       none
 *
 * outputs:
 *       none
 *
 * side effects:
 *       registered sockets are prepared for the poll() loop.
 */
static void update_poll_fds(void)
{
	node_t *n;
	connection_t *cptr;
	int slot = 0;

	LIST_FOREACH(n, connection_list.head)
	{
		cptr = n->data;

		cptr->pollslot = slot;

		if (CF_IS_CONNECTING(cptr) || sendq_nonempty(cptr))
		{
			pollfds[slot].fd = cptr->fd;
			pollfds[slot].events |= POLLWRNORM;
			pollfds[slot].revents = 0;
		}
		else
		{
			pollfds[slot].fd = cptr->fd;
			pollfds[slot].events |= POLLRDNORM;
			pollfds[slot].revents = 0;
		}
		slot++;
	}
}

/*
 * connection_select()
 *
 * inputs:
 *       delay in microseconds
 *
 * outputs:
 *       none
 *
 * side effects:
 *       registered sockets and their associated handlers are acted on.
 */
void connection_select(time_t delay)
{
	int sr;
	node_t *n, *tn;
	connection_t *cptr;
	int slot;

	update_poll_fds();

	if ((sr = poll(pollfds, connection_list.count, delay / 100)) > 0)
	{
		/* Iterate twice, so we don't touch freed memory if
		 * a connection is closed.
		 * -- jilles */
		LIST_FOREACH_SAFE(n, tn, connection_list.head)
		{
			cptr = n->data;
			slot = cptr->pollslot;

			if (pollfds[slot].revents == 0)
				continue;

			if (pollfds[slot].revents & (POLLRDNORM | POLLIN | POLLHUP | POLLERR))
			{
				pollfds[slot].events &= ~(POLLRDNORM | POLLIN | POLLHUP | POLLERR);
				cptr->read_handler(cptr);
			}
		}

		LIST_FOREACH_SAFE(n, tn, connection_list.head)
		{
			cptr = n->data;
			slot = cptr->pollslot;

			if (pollfds[slot].revents == 0)
				continue;
			if (pollfds[slot].revents & (POLLWRNORM | POLLOUT | POLLHUP | POLLERR))
			{
				pollfds[slot].events &= ~(POLLWRNORM | POLLOUT | POLLHUP | POLLERR);
				if (CF_IS_CONNECTING(cptr))
					hook_call_event("connected", cptr);
				else
					cptr->write_handler(cptr);
			}
		}

		LIST_FOREACH_SAFE(n, tn, connection_list.head)
		{
			cptr = n->data;
			if (cptr->flags & CF_DEAD)
				connection_close(cptr);
		}
	}
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */
