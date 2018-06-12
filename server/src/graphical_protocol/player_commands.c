/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** player related graphical protocol commands related functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "entity.h"

bool handle_ppo(game_t *game, char *arguments)
{
	int player_number;
	player_t *player;
	int orientation;

	if (!arguments || arguments[0] != '#' || !arguments[1] ||
		arguments[1] < '0' || arguments[1] > '9')
		return (false);
	player_number = atoi(&arguments[1]);
	player = player_by_fd(game->players, player_number);
	if (!player)
		return (false);
	if (player->entity.facing % 4 == 0)
		orientation = player->entity.facing / 2 + 1;
	else
		orientation = player->entity.facing % 6 + 2;
	fprintf(game->graph_stream, "ppo %i %i %i %i\n", player->fd,
		(int)player->entity.pos.x, (int)player->entity.pos.y,
		orientation);
	return (true);
}

bool handle_plv(game_t *game, char *arguments)
{
	int player_nb;
	player_t *player;

	if (!arguments || arguments[0] != '#' || !arguments[1] ||
		arguments[1] < '0' || arguments[1] > '9')
		return (false);
	player_nb = atoi(&arguments[1]);
	player = player_by_fd(game->players, player_nb);
	if (!player)
		return (false);
	fprintf(game->graph_stream, "plv %i %i", player_nb,
		player->entity.level);
	return (true);
}

bool handle_pin(game_t *game, char *arguments)
{
	int player_nb;
	player_t *player;
	int *inv;

	if (!arguments || arguments[0] != '#' || !arguments[1] ||
		arguments[1] < '0' || arguments[1] > '9')
		return (false);
	player_nb = atoi(&arguments[1]);
	player = player_by_fd(game->players, player_nb);
	if (!player)
		return (false);
	inv = (int *)player;
	fprintf(game->graph_stream, "pin %i %i %i %i %i %i %i %i %i %i\n",
		player->fd, (int)player->entity.pos.x,
		(int)player->entity.pos.y, inv[0], inv[1], inv[2], inv[3],
		inv[4], inv[5], inv[6]);
	return (true);
}

bool handle_tna(game_t *game, char *arguments)
{
	int i = -1;

	if (arguments)
		return (false);
	while (game->teams[++i].name) {
		fprintf(game->graph_stream, "tna %s\n", game->teams[i].name);
	}
	return (true);
}
