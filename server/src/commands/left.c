/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Left command handling
*/

#include "game.h"
#include "entity.h"
#include "graphical_commands.h"

bool respond_left(game_t *game, player_t *player, char *argument)
{
	(void)game;
	if (argument)
		return (false);
	player->entity.facing = direction_left(player->entity.facing);
	fprintf(player->stream, "ok\n");
	send_ptu(game->graph_stream, player->id, player->entity.facing);
	return (true);
}
