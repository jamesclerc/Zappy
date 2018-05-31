/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Socket Helpers
*/

#include <arpa/inet.h>
#include <string.h>

/// Create a listening socket for all interfaces
//  `uint16_t port`: The port to listen on
//  `int backlog`: The size of the backlog used by `listen`
//  `int return`: The resulting file descriptor or -1
int socket_listen(uint16_t port, int backlog)
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
