/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** New client connection related functions
*/

#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include "game.h"
#include "entity.h"
#include "communication.h"
#include "commands.h"
#include "leave.h"

static command_t commands[] = {
	{"Forward", 7, &handle_forward},
	{"Right", 7, &handle_right},
	{"Left", 7, &handle_left},
	{"Look", 7, NULL},
	{"Inventory", 1, &handle_inventory},
	{"Broadcast", 7, NULL},
	{"Connect_nbr", 0, NULL},
	{"Fork", 42, NULL},
	{"Eject", 7, NULL},
	{"Take", 7, NULL},
	{"Set", 7, NULL},
	{"Incantation", 300, NULL},
	{NULL, 0, NULL}
};

static bool accept_client(game_t *game, struct epoll_event *ev, int epoll_fd)
{
	player_t *new;
	int client_fd = accept(ev->data.fd, NULL, NULL);

	if (client_fd < 0)
		return (false);
	new = player_create(client_fd);
	if (!new)
		return (false);
	new->entity.facing = (rand() % 4) * 2;
	new->entity.pos.x = rand() % game->map->width;
	new->entity.pos.y = rand() % game->map->height;
	list_insert(&(game->players), (void *)new);
	epoll_watch(epoll_fd, new->fd);
	fprintf(new->stream, "WELCOME\n");
	return (true);
}

static bool interpret_message(game_t *game, player_t *player, char *message)
{
	size_t i = 0;

	if (player->entity.team == NULL) {
		if (link_player_team(game->teams, player, message)) {
			fprintf(player->stream, "%i\n%ld %ld\n", player->fd,
				game->map->width, game->map->height);
			return (true);
		}
		fprintf(player->stream, "ko\n");
		return (false);
	}
	for (i = 0; commands[i].name != NULL; i++)
		if (strcasecmp(message, commands[i].name) == 0)
			break;
	if (commands[i].name == NULL) {
		fprintf(player->stream, "ko\n");
		return (false);
	}
	return (queue_action(player, commands + i));
}

static bool get_message(game_t *game, int fd)
{
	player_t *player = player_by_fd(game->players, fd);
	char *message = NULL;
	size_t i = 0;
	bool result;

	if (player == NULL)
		return (false);
	if (getline(&message, &i, player->stream) == -1) {
		player_remove(&game->players, player);
		return (false);
	}
	if (message == NULL)
		return (false);
	message[strcspn(message, "\r\n")] = '\0';
	if (strlen(message) == 0) {
		free(message);
		return (true);
	}
	message = strtok(message, " ");
	result = interpret_message(game, player, message);
	free(message);
	return (result);
}

static bool disconnect_handle(game_t *game, struct epoll_event *ev)
{
	list_t *tmp;
	player_t *player;

	tmp = game->players;
	while (tmp) {
		player = (player_t *)tmp->element;
		if (player->fd == ev->data.fd) {
			list_remove(&tmp);
			player_destroy(player);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

bool event_handle(game_t *game, struct epoll_event *ev, int efd, int sfd)
{
	if (ev->events & EPOLLIN && ev->data.fd == sfd)
		return (accept_client(game, ev, efd));
	else if (ev->data.fd == sfd)
		err(84, "pterodactyl scream"); // AAAAAAAAH!
	else if (ev->events & EPOLLIN)
		return (get_message(game, ev->data.fd));
	else
		disconnect_handle(game, ev);
	return (false);
}
