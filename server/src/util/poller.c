/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Polling Helpers
*/

#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

/// Add a data source to a poller's watching list
//  `int pollfd`: The poller's file descriptor
//  `int datafd`: The file descriptor to watch for events
//  `int return`: Zero on success
int epoll_watch(int pollfd, int datafd)
{
	struct epoll_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLERR;
	ev.data.fd = datafd;
	if (epoll_ctl(pollfd, EPOLL_CTL_ADD, datafd, &ev) < 0) {
		close(datafd);
		return (-1);
	}
	return (0);
}

/// Prepare a new poller and add an initial data source to its list
//  `int datafd`: The file descriptor to watch for events
//  `int return`: The poller's file descriptor or -1
int epoll_prepare(int datafd)
{
	int pollfd = epoll_create1(0);

	if (pollfd < 0 || epoll_watch(pollfd, datafd) < 0)
		return (-1);
	return (pollfd);
}
