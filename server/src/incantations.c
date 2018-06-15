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
#include "graphical_commands.h"

static void interrupt_incantation(game_t *game, list_t *tmp)
{
	int i = -1;
	struct timeval curtime;
	incantation_t *inc = tmp->element;

	gettimeofday(&curtime, NULL);
	fprintf(inc->participants[0]->stream, "ko\n");
	send_pie(game->graph_stream, inc->participants[0]->fd, false);
	while (++i < 6 && inc->participants[i]) {
		queue_pop(inc->participants[i]->commands, NULL);
		if (inc->participants[i]->commands->tail)
			memcpy(&((action_t*)inc->participants[i]->commands
			->tail->element)->start_time, &curtime,
			sizeof(struct timeval));
	}
	list_remove((tmp == game->incantations) ? &game->incantations : &tmp);
}

void incantations_check(game_t *game)
{
	list_t *tmp = game->incantations;
	incantation_t *inc;

	while (tmp) {
		inc = tmp->element;
		if (!inventory_has(&game->map->cells[inc->participants[0]->
			entity.pos.y][inc->participants[0]->entity.pos.x],
			(inventory_t *)&elevations
			[inc->participants[0]->entity.level])){
			interrupt_incantation(game, tmp);
		}
		tmp = tmp->next;
	}
}
