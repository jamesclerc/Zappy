/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command queue related functions
*/

#include <sys/time.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "entity.h"
#include "commands.h"
#include "incantation.h"

static void check_and_exec(game_t *game, player_t *player)
{
	action_t *action = player->commands->tail->element;
	struct timeval tv[3];

	if (gettimeofday(&tv[0], NULL) < 0)
		err(84, "gettimeofday");
	tv[1].tv_sec = action->command->duration / game->freq;
	tv[1].tv_usec = (1000000 * (action->command->duration % game->freq)
		/ game->freq);
	timeradd(&action->start_time, &tv[1], &tv[2]);
	if (!timercmp(&tv[0], &tv[2], <)) {
		if (!action->command->respond(game, player, action->argument))
			fprintf(player->stream, "ko\n");
		queue_pop(player->commands, NULL);
		if (player->commands->tail)
			memcpy(&((action_t *)player->commands->tail->element)
				->start_time, &tv[0], sizeof(struct timeval));
	}
}

void execute_commands(game_t *game)
{
	list_t *tmp = game->players;
	player_t *player;

	while (tmp) {
		player = tmp->element;
		if (player->commands->head) {
			check_and_exec(game, player);
		}
		tmp = tmp->next;
	}
}

static void queue_incantation(game_t *game, player_t *p, action_t *to_queue)
{
	incantation_t *element = game->incantations->element;
	action_t *new;
	int i = 0;

	while (i < 6 && element->participants[i] != NULL) {
		if (element->participants[i] != p) {
			new = malloc(sizeof(action_t));
			if (!new)
				return;
			new->start_time = to_queue->start_time;
			new->command = to_queue->command;
			new->argument = (to_queue->argument) ?
			strdup(to_queue->argument) : NULL;
			queue_push(element->participants[i]->commands, new);
		}
		i++;
	}
}

bool queue_action(game_t *game, player_t *player, command_t *command)
{
	action_t *action;
	char *argument = NULL;

	argument = strtok(NULL, "");
	if (command->respond == NULL)
		return (false);
	if (command->handle && !command->handle(game, player, argument))
		return (false);
	action = malloc(sizeof(action_t));
	if (action == NULL)
		return (false);
	memset(action, 0, sizeof(action_t));
	gettimeofday(&action->start_time, NULL);
	action->command = command;
	if (argument != NULL && strlen(argument) != 0)
		action->argument = strdup(argument);
	queue_push(player->commands, action);
	if (command->handle == &handle_incantation)
		queue_incantation(game, player, action);
	return (true);
}
