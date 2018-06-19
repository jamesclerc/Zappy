/*
** EPITECH PROJECT, 2018
** Communication.cpp
** File description:
** Communication cpp
*/

#include "Communication.hpp"


gpc::Communication(std::string ip, int port) : _ip(ip), _port(port)
{
}

gpc::~Communication()
{
}

gpc::Communication::firstConnection()
{
}


int gpc::Communication::socket_listen(uint16_t port, int backlog)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;

	if (sockfd < 0)
		return (-1);
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0)
		return (-1);
	if (listen(sockfd, backlog) < 0)
		return (-1);
	return (sockfd);
}

/// Add a data source to a poller's watching list
//  `int pollfd`: The poller's file descriptor
//  `int datafd`: The file descriptor to watch for events
//  `int return`: Zero on success
int gpc::Communication::epoll_watch(int pollfd, int datafd)
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
int gpc::Communication::epoll_prepare(int datafd)
{
	int pollfd = epoll_create1(0);

	if (pollfd < 0 || epoll_watch(pollfd, datafd) < 0)
		return (-1);
	return (pollfd);
}