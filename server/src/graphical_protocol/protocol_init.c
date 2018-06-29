/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Graphical protocol initialization functions
*/

#include <stdio.h>
#include "game.h"
#include "containers.h"
#include "entity.h"
#include "graphical_commands.h"

static void send_initial_incantations(game_t *game)
{
	list_t *tmp = game->incantations;
	incantation_t *inc;

	while (tmp) {
		inc = tmp->element;
		send_pic(game->graph_stream, inc);
		tmp = tmp->next;
	}
}

static void send_initial_eggs(game_t *game)
{
	list_t *tmp = game->hatching_eggs->head;
	egg_t *egg;

	while (tmp) {
		egg = tmp->element;
		send_neg(game->graph_stream, egg);
		tmp = tmp->next;
	}
	for (unsigned int i = 0; game->teams[i].name; i++) {
		tmp = game->teams[i].eggs->head;
		while (tmp) {
			egg = tmp->element;
			send_neg(game->graph_stream, egg);
			send_heg(game->graph_stream, egg->id);
			tmp = tmp->next;
		}
	}
}

static bool show_tile(game_t *game, int x, int y)
{
	int *cell;

	if (x < 0 || x >= (int)game->map->width || y < 0 ||
	y >= (int)game->map->height)
		return (false);
	cell = (int *)&game->map->cells[y][x];
	fprintf(game->graph_stream, "bct %i %i %i %i %i %i %i %i %i\n", x, y,
		cell[0], cell[1], cell[2], cell[3], cell[4], cell[5], cell[6]);
	return (true);
}

static void send_initial_players(game_t *game)
{
	list_t *tmp = game->players;
	player_t *player;

	while (tmp) {
		player = tmp->element;
		send_pnw(game->graph_stream, player);
		tmp = tmp->next;
	}
}

void graphical_protocol_init(game_t *game)
{
	fprintf(game->graph_stream, "tgt %i\n", game->freq);
	fprintf(game->graph_stream, "msz %li %li\n", game->map->width,
		game->map->height);
	for (unsigned int i = 0; i < game->map->height; i++) {
		for (unsigned int j = 0; j < game->map->width; j++) {
			show_tile(game, j, i);
		}
	}
	send_initial_players(game);
	send_initial_eggs(game);
	send_initial_incantations(game);
}
