/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Connect_nbr command related
*/

#include <stdbool.h>
#include "game.h"
#include "entity.h"

bool respond_connect_nbr(game_t *game, player_t *player,  char *argument)
{
	(void)game;
	if (argument) {
		return (false);
	}
	fprintf(player->stream, "%i\n", (int)player->entity.team->slots);
	return (true);
}
