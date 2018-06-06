/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Inventory command related functions
*/

#include "game.h"
#include "entity.h"

bool handle_inventory(game_t *game, player_t *player, char *argument)
{
	(void)game;
	if (argument)
		return (false);
	fprintf(player->stream, "[ food %i, linemate %i, deraumere %i, "
		"sibur %i, mendiane %i, phiras %i, thystame %i ]\n",
		player->entity.inventory.food,
		player->entity.inventory.linemate,
		player->entity.inventory.deraumere,
		player->entity.inventory.sibur,
		player->entity.inventory.mendiane,
		player->entity.inventory.phiras,
		player->entity.inventory.thystame);
	return (true);
}
