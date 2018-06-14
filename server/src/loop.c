/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** server's main loop functions
*/

#include <stdbool.h>
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "communication.h"
#include "containers.h"
#include "space.h"
#include "team.h"
#include "game.h"
#include "food.h"
#include "incantation.h"
#include "egg.h"

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
		incantations_check(game);
		hatch_egg(game);
		map_fill(game->map);
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
	game->hatching_eggs = queue_create(sizeof(egg_t));
	loop(game, epoll_fd, server_fd);
	close(epoll_fd);
	fclose(game->graph_stream);
	return (true);
}
