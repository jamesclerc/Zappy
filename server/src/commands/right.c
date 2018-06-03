/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Right command Handling
*/

#include "game.h"
#include "entity.h"

bool handle_right(game_t *game, player_t *player, char *argument)
{
	if (argument) {
		fprintf(player->stream, "ko\n");
		return (false);
	}
	(void)game;
	return (true);
}

void respond_right(game_t *game, player_t *player, char *argument)
{
	(void)game;
	(void)argument;
	player->entity.facing = direction_right(player->entity.facing);
	fprintf(player->stream, "ok\n");
}
