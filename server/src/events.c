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

static command_t commands[] = {
	{"Forward", 7, &handle_forward, &respond_forward},
	{"Right", 7, &handle_right, &respond_right},
	{"Left", 7, &handle_left, &respond_left},
	{"Look", 7, NULL, NULL},
	{"Inventory", 1, &handle_inventory, &respond_inventory},
	{"Broadcast", 7, NULL, NULL},
	{"Connect_nbr", 0, NULL, NULL},
	{"Fork", 42, NULL, NULL},
	{"Eject", 7, NULL, NULL},
	{"Take", 7, NULL, NULL},
	{"Set", 7, NULL, NULL},
	{"Incantation", 300, NULL, NULL},
	{NULL, 0, NULL, NULL}
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
	list_insert(&(game->players), (void *)new);
	epoll_watch(epoll_fd, new->fd);
	return (true);
}

static bool queue_action(game_t *game, player_t *player, command_t *command)
{
	action_t *action;
	char *argument;

	argument = strtok(NULL, "");
	if (command->handle != NULL && !command->handle(game, player, argument))
		return (false);
	if (command->duration != 0) {
		action = malloc(sizeof(action_t));
		if (action == NULL)
			return (false);
		memset(action, 0, sizeof(action_t));
		gettimeofday(&action->start_time, NULL);
		action->command = command;
		if (argument != NULL && strlen(argument) != 0)
			action->argument = strdup(argument);
		queue_push(player->commands, action);
	}
	return (true);
}

static bool get_message(game_t *game, int fd)
{
	player_t *player = player_by_fd(game->players, fd);
	char *message = NULL;
	size_t i = 0;
	bool result;

	if (player == NULL)
		return (false);
//	if (player->entity.team == NULL)
//		return (false); // TODO: Receive team name, place player and send info
	getline(&message, &i, player->stream);
	if (message == NULL)
		return (false);
	message[strcspn(message, "\r\n")] = '\0';
	if (strlen(message) == 0) {
		free(message);
		return (true);
	}
	message = strtok(message, " ");
	for (i = 0; commands[i].name != NULL; i++)
		if (strcasecmp(message, commands[i].name) == 0)
			break;
	result = queue_action(game, player, commands + i);
	free(message);
	return (result);
}

bool event_handle(game_t *game, struct epoll_event *ev, int efd, int sfd)
{
	if (ev->events & EPOLLIN && ev->data.fd == sfd)
		return (accept_client(game, ev, efd));
	else if (ev->data.fd == sfd)
		err(84, "pterodactyl scream"); // AAAAAAAAH!
	else if (ev->events & EPOLLIN)
		return (get_message(game, ev->data.fd));
	else {
		player_destroy(player_by_fd(game->players, ev->data.fd));
	}
	return (false);
}
