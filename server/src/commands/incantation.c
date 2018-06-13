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
		return (player->entity.team &&
			player != self && !player->commands &&
			player->entity.level == self->entity.level);
	else
		return (player->entity.team && player != self &&
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
	fprintf(p->stream, "Elevation underway\n");
	return (true);
}

static void incantation_remove(list_t **head, list_t *tmp)
{
	incantation_t *inc = tmp->element;
	player_t *p;
	int i = -1;

	while (++i < 6 && inc->participants[i]) {
		p = inc->participants[i];
		fprintf(p->stream, "Current level: %i\n", ++p->entity.level);
		if (p->entity.level == 8)
			p->entity.team->overlords++;
	}
	list_remove((tmp == *head) ? head : &tmp);
}

bool respond_incantation(game_t *game, player_t *p, char *argument)
{
	list_t *tmp = game->incantations;
	incantation_t *i;

	(void)argument;
	if (!inventory_has(&game->map->cells[p->entity.pos.y][p->entity.pos.x],
	(inventory_t *)(&elevations[p->entity.level - 1])) ||
		!elevation_check_players(game->players, p, NULL)) {
		return (false);
	}
	while (tmp) {
		i = tmp->element;
		if (i->participants[0] == p){
			incantation_remove(&game->incantations, tmp);
			break;
		}
		tmp =tmp->next;
	}
	return (true);
}
