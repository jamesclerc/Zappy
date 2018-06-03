/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** server's main loop functions
*/

#include <stdbool.h>
#include <sys/epoll.h>
#include "commands.h"
#include "communication.h"
#include "containers.h"
#include "space.h"
#include "team.h"
#include "game.h"

static bool loop(game_t *game, int efd, int sfd)
{
	struct epoll_event events[QUEUE_SIZE];
	int n = 0;

	for (;;) {
		//printf("Loop !\n");
		n = epoll_wait(efd, events, QUEUE_SIZE, 0);
		for (int i = 0; i < n; i++)
			event_handle(game, events + i, efd, sfd);
		execute_commands(game);
	}
	return (true);
}

/// Initializes the server main socket and epoll instance to call the main loop
bool serve(game_t *game, int *args)
{
	int server_fd = socket_listen(args[0], QUEUE_SIZE);
	int epoll_fd;

	if (server_fd < 0)
		return (false);
	epoll_fd = epoll_prepare(server_fd);
	if (epoll_fd < 0)
		return (false);
	loop(game, epoll_fd, server_fd);
	return (true);
}
