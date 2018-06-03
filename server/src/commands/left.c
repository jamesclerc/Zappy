/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Left command handling
*/

#include "game.h"
#include "entity.h"

bool handle_left(game_t *game, player_t *player, char *argument)
{
	if (argument) {
		fprintf(player->stream, "ko\n");
		return (false);
	}
	(void)game;
	return (true);
}

void respond_left(game_t *game, player_t *player, char *argument)
{
	(void)game;
	(void)argument;
	player->entity.facing = direction_left(player->entity.facing);
	fprintf(player->stream, "ok\n");
}
