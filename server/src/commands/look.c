/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Look command related functions
*/

#include "game.h"
#include "entity.h"

static bool list_cell_items(FILE *stream, bool first, size_t item,
	inventory_t *inv)
{
	int *tab = (int *)inv;
	int count = -1;

	if (tab[item] <= 0)
		return (false);
	while (++count < tab[item]) {
		fprintf(stream, (first) ? "%s" : " %s", item_names[item]);
		first = false;
	}
	return (first);
}

static bool list_cell_players(FILE *stream, list_t *players, position_t pos,
	bool first)
{
	list_t *tmp = players;

	while (tmp) {
		if (((player_t *)tmp->element)->entity.team &&
			((player_t *)tmp->element)->entity.pos.x == pos.x &&
			((player_t *)tmp->element)->entity.pos.y == pos.y) {
			fprintf(stream, (first) ? "%s" : " %s", "player");
			first = false;
		}
		tmp = tmp->next;
	}
	return (first);
}

static void show_cell(FILE *stream, game_t *game, position_t pos)
{
	bool first = true;
	size_t i = 0;

	first = list_cell_players(stream, game->players, pos, first);
	while (i < sizeof(inventory_t) / sizeof(int)) {
		first = list_cell_items(stream, first, i++,
			&game->map->cells[pos.y][pos.x]);
	}
}

bool respond_look(game_t *game, player_t *player, char *argument)
{
	int i = -1;
	position_t tmp = player->entity.pos;
	direction_t dir = player->entity.facing;

	if (argument)
		return (false);
	fprintf(player->stream, "[");
	show_cell(player->stream, game, tmp);
	while (++i <= player->entity.level) {
		position_nudge(game->map, &tmp, dir);
		if (i % 2 == 1)
			dir = direction_left(dir);
		else
			dir = direction_right(dir);
		position_nudge(game->map, &tmp, dir);
		if (i % 2 == 1)
			dir = direction_left(dir);
		else
			dir = direction_right(dir);
		for (int j = 0; j < i * 2; ++j) {
			fprintf(player->stream, ",");
			show_cell(player->stream, game, tmp);
			position_nudge(game->map, &tmp, dir);
		}
	}
	fprintf(player->stream, "]\n");
	return (true);
}
