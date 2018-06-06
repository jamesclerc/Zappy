/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Forward command related functions
*/

#include "game.h"
#include "entity.h"

bool respond_forward(game_t *game, player_t *player, char *argument)
{
	if (argument) {
		return (false);
	}
	position_nudge(game->map, &player->entity.pos, player->entity.facing);
	fprintf(player->stream, "ok\n");
	return (true);
}
