/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Set command related functions
*/

#include <string.h>
#include "game.h"
#include "entity.h"
#include "graphical_commands.h"

bool respond_set(game_t *game, player_t *player, char *argument)
{
	inventory_t amount;
	inventory_t *cell;
	int i = 0;

	memset(&amount, 0, sizeof(inventory_t));
	if (!argument || strlen(argument) == 0)
		return (false);
	while (item_names[i] && strcmp(item_names[i], argument) != 0)
		i++;
	if (!item_names[i])
		return (false);
	((int *)(&amount))[i]++;
	cell = &game->map->cells[player->entity.pos.y][player->entity.pos.x];
	if (!inventory_take((inventory_t *)player, &amount))
		return (false);
	inventory_give(cell, &amount);
	send_pdr(game->graph_stream, player->fd, i);
	fprintf(player->stream, "ok\n");
	return (true);
}
