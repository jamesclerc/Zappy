/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** New client connection related functions
*/

#include <stdbool.h>
#include <sys/epoll.h>
#include "game.h"
#include "entity.h"
#include "communication.h"

bool accept_client(game_t *game, struct epoll_event *ev, int epoll_fd)
{
	player_t *new = player_create(ev->data.fd);

	if (!new)
		return (false);
	list_insert(&(game->players), (void *)new);
	epoll_watch(epoll_fd, new->fd);
	return (true);
}
