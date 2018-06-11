/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Eject command related functions
*/

#include "game.h"
#include "entity.h"

static direction_t eject_origin(direction_t eject_facing,
	direction_t ejected_facing)
{
	direction_t res;

	res = eject_facing + 4 % DIR_COUNT;
	res = res - ejected_facing;
	if (res < 0)
		res += DIR_COUNT;
	return (res + 1);
}

bool respond_eject(game_t *game, player_t *player, char *argument)
{
	list_t *list = game->players;
	player_t *tmp;
	bool ret = false;

	if (argument)
		return (false);
	while (list) {
		tmp = list->element;
		if (tmp->entity.team &&
			tmp->entity.pos.y == player->entity.pos.y &&
			tmp->entity.pos.x == player->entity.pos.x) {
			position_nudge(game->map, &tmp->entity.pos,
				player->entity.facing);
			fprintf(tmp->stream, "eject: %i\n",
				eject_origin(player->entity.facing,
				tmp->entity.facing));
			ret = true;
		}
		list = list->next;
	}
	return (ret);
}
