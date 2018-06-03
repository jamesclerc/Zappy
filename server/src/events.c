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
#include "commands.h"

static command_t commands[] = {
	{"Forward", 7, NULL, NULL},
	{"Right", 7, NULL, NULL},
	{"Left", 7, NULL, NULL},
	{"Look", 7, NULL, NULL},
	{"Inventory", 1, NULL, NULL},
	{"Broadcast", 7, NULL, NULL},
	{"Connect_nbr", 0, NULL, NULL},
	{"Fork", 42, NULL, NULL},
	{"Eject", 7, NULL, NULL},
	{"Take", 7, NULL, NULL},
	{"Set", 7, NULL, NULL},
	{"Incantation", 300, NULL, NULL},
	{NULL, 0, NULL, NULL}
};

bool accept_client(game_t *game, struct epoll_event *ev, int epoll_fd)
{
	player_t *new = player_create(ev->data.fd);

	if (!new)
		return (false);
	list_insert(&(game->players), (void *)new);
	epoll_watch(epoll_fd, new->fd);
	return (true);
}
