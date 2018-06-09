/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** server's main loop functions
*/

#include <stdbool.h>
#include <sys/epoll.h>
#include <string.h>
#include "commands.h"
#include "communication.h"
#include "containers.h"
#include "space.h"
#include "team.h"
#include "game.h"
#include "food.h"
#include "incantation.h"

static void interrupt_incantation(game_t *game, list_t *tmp)
{
	int i = -1;
	struct timeval curtime;
	incantation_t *inc = tmp->element;

	gettimeofday(&curtime, NULL);
	while (++i < 6 && inc->participants[i]) {
		fprintf(inc->participants[i]->stream, "ko\n");
		queue_pop(inc->participants[i]->commands, NULL);
		if (inc->participants[i]->commands->tail)
			memcpy(&((action_t*)inc->participants[i]->commands
			->tail->element)->start_time, &curtime,
			sizeof(struct timeval));
	}
	list_remove((tmp == game->incantations) ? &game->incantations : &tmp);
}

static bool check_players(incantation_t *inc)
{
	int i = -1;

	while (++i < 6 && inc->participants[i]) {
		if (inc->participants[i]->entity.pos.x != inc->pos.x ||
			inc->participants[i]->entity.pos.y != inc->pos.y)
			return (false);
	}
	return (true);
}

static void check_incantations(game_t *game)
{
	list_t *tmp = game->incantations;
	incantation_t *inc;

	while (tmp) {
		inc = tmp->element;
		if (!inventory_has(&game->map->cells[inc->pos.y][inc->pos.x], (inventory_t *) &elevations[inc->participants[0]->entity.level])
		||!check_players(inc)) {
			interrupt_incantation(game, tmp);
		}
		tmp = tmp->next;
	}
}

static bool loop(game_t *game, int efd, int sfd)
{
	struct epoll_event events[QUEUE_SIZE];
	int n = 0;

	for (;;) {
		n = epoll_wait(efd, events, QUEUE_SIZE, 0);
		for (int i = 0; i < n; i++)
			event_handle(game, events + i, efd, sfd);
		execute_commands(game);
		food_update(&game->players, game->freq);
		check_incantations(game);
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
