/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Forward command related functions
*/

#include "game.h"
#include "entity.h"

bool handle_forward(game_t *game, player_t *player, char *argument)
{
	if (argument) {
		fprintf(player->stream, "ko\n");
		return (false);
	}
	(void)game;
	return (true);
}

bool respond_forward(game_t *game, player_t *p, char *argument)
{
	(void)argument;
	position_nudge(game->map, &p->entity.pos, p->entity.facing);
	return (true);
}
