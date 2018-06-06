/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Left command handling
*/

#include "game.h"
#include "entity.h"

bool respond_left(game_t *game, player_t *player, char *argument)
{
	(void)game;
	if (argument)
		return (false);
	player->entity.facing = direction_left(player->entity.facing);
	fprintf(player->stream, "ok\n");
	return (true);
}
