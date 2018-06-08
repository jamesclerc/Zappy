/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Incantation command related functions
*/

#include <stdlib.h>
#include <err.h>
#include "game.h"
#include "entity.h"
#include "incantation.h"

static bool el_player_is_valid(player_t *self, player_t *player,
	bool fill_participants)
{
	if (fill_participants)
		return (player != self && !player->commands &&
			player->entity.level == self->entity.level);
	else
		return (player != self &&
			player->entity.level == self->entity.level);
}

static bool elevation_check_players(list_t *players, player_t *p,
	player_t **participants)
{
	list_t *tmp = players;
	player_t *player;
	int required = (p->entity.level != 1) ? ((p->entity.level / 2) * 2) : 1;
	int count = 1;
	bool valid;

	while (tmp) {
		player = (player_t *)tmp->element;
		valid = el_player_is_valid(player, p, participants != NULL);
		if (participants && valid) {
			participants[count] = player;
			count++;
		} else if (valid)
			count++;
		tmp = tmp->next;
	}
	if (participants && count <= 5)
		participants[count] = NULL;
	return (count >= required);
}

bool handle_incantation(game_t *game, player_t *p, char *argument)
{
	incantation_t *new = malloc(sizeof(incantation_t));

	if (!new)
		err(84, "malloc");
	new->pos = p->entity.pos;
	new->actions_queued = false;
	new->participants[0] = p;
	if (argument||!inventory_has(
		&game->map->cells[p->entity.pos.y][p->entity.pos.x],
		(inventory_t *)&elevations[p->entity.level - 1]) ||
		!elevation_check_players(game->players, p, new->participants)) {
			free(new);
			fprintf(p->stream, "ko\n");
			return (false);
	}
	list_insert(&game->incantations, new);
	fprintf(p->stream, "ok\n");
	return (true);
}

bool respond_incantation(game_t *game, player_t *p, char *argument)
{
	list_t *tmp = game->incantations;
	incantation_t *inc;

	(void)argument;
	if (!inventory_has(&game->map->cells[p->entity.pos.y][p->entity.pos.x],
	(inventory_t *)(&elevations[p->entity.level - 1])) ||
		!elevation_check_players(game->players, p, NULL)) {
		fprintf(p->stream, "ko\n");
		return (false);
	}
	while (tmp) {
		inc = tmp->element;
		if (inc->pos.x == p->entity.pos.x &&
			inc->pos.y == p->entity.pos.y &&
			inc->participants[0] == p) {
			list_remove((tmp == game->incantations) ?
			&game->incantations : &tmp);
		}
		tmp =tmp->next;
	}
	fprintf(p->stream, "ok\n");
	return (true);
}
