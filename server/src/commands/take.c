/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Take object command related functions
*/

#include "game.h"
#include "entity.h"
#include "string.h"
#include "inventory.h"
#include "space.h"

bool respond_take(game_t *game, player_t *player, char *argument)
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
	((int*)(&amount))[i]++;
	cell = &game->map->cells[player->entity.pos.y][player->entity.pos.x];
	if (!inventory_take(cell, &amount))
		return (false);
	fprintf(player->stream, "ok\n");
	return (true);
}
