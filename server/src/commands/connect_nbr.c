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
	list_t *tmp = player->entity.team->eggs->head;
	int eggs = 0;

	(void)game;
	if (argument) {
		return (false);
	}
	while (tmp) {
		eggs++;
		tmp = tmp->next;
	}
	fprintf(player->stream, "%i\n", (int)player->entity.team->slots + eggs);
	return (true);
}
