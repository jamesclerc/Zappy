/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Incantation related commands
*/

#include <string.h>
#include "game.h"
#include "incantation.h"
#include "containers.h"
#include "commands.h"

static void interrupt_incantation(game_t *game, list_t *tmp)
{
	int i = -1;
	struct timeval curtime;
	incantation_t *inc = tmp->element;

	gettimeofday(&curtime, NULL);
	while (++i < 6 && inc->participants[i]) {
		fprintf(inc->participants[i]->stream, "ko\n");
		queue_pop(inc->participants[i]->commands, NULL);
		if (inc->participants[i]->commands->tail)
			memcpy(&((action_t*)inc->participants[i]->commands
			->tail->element)->start_time, &curtime,
			sizeof(struct timeval));
	}
	list_remove((tmp == game->incantations) ? &game->incantations : &tmp);
}

static bool check_players(incantation_t *inc)
{
	int i = -1;

	while (++i < 6 && inc->participants[i]) {
		if (inc->participants[i]->entity.pos.x != inc->pos.x ||
			inc->participants[i]->entity.pos.y != inc->pos.y)
			return (false);
	}
	return (true);
}

void incantations_check(game_t *game)
{
	list_t *tmp = game->incantations;
	incantation_t *inc;

	while (tmp) {
		inc = tmp->element;
		if (!inventory_has(&game->map->cells[inc->pos.y][inc->pos.x],
			(inventory_t *)&elevations[inc->participants[0]
			->entity.level])
		||!check_players(inc)) {
			interrupt_incantation(game, tmp);
		}
		tmp = tmp->next;
	}
}
