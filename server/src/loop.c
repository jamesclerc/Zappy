/*
** EPITECH PROJECT, 2018
** loop.c
** File description:
** server's main loop functions
*/

#include <stdbool.h>
#include "containers.h"
#include "space.h"
#include "team.h"
#include "util.h"
#include "game.h"

static bool loop(game_t *game, int epoll_fd, int server_fd)
{
	for (;;) {
		//Interroger epoll
		//Ajouter les commandes aux queues des players en question
		//Checker pour chaque player la commandes a executer
	}
	(void)game;
	(void)epoll_fd;
	(void)server_fd;
	return (true);
}

bool serv(game_t *game, int *args)
{
	int server_fd = socket_listen(args[0], 16);
	int epoll_fd;

	if (server_fd < 0)
		return (false);
	epoll_fd = epoll_prepare(server_fd);
	if (epoll_fd < 0)
		return (false);
	loop(game, epoll_fd, server_fd);
	return (true);
}
