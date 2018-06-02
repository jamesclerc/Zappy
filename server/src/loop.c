/*
** EPITECH PROJECT, 2018
** loop.c
** File description:
** server's main loop functions
*/

#include <stdbool.h>
#include "containers.h"
#include "map.h"
#include "team.h"
#include "util.h"

bool loop(map_t *map, team_t *teams, int epoll_fd, int server_fd)
{
	list_t *players = NULL;

	while (1) {
		//Interroger epoll
		//Ajouter les commandes aux queues des players en question
		//Checker pour chaque player la commandes a executer
	}
	(void)players;
	(void)map;
	(void)teams;
	(void)epoll_fd;
	(void)server_fd;
}

bool init_loop(map_t *map, team_t *teams, int *args)
{
	int server_fd = socket_listen(args[0], 16);
	int epoll_fd;

	if (server_fd < 0)
		return (false);
	epoll_fd = epoll_prepare(server_fd);
	if (epoll_fd < 0)
		return (false);
	loop(map, teams, epoll_fd, server_fd);
	return (true);
}
