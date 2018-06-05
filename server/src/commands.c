/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command queue related functions
*/

#include <sys/time.h>
#include <err.h>
#include <string.h>
#include "game.h"
#include "entity.h"
#include "commands.h"

static void check_and_exec(game_t *game, player_t *player)
{
	action_t *action = player->commands->head->element;
	struct timeval tv[3];
	action_t memory;

	if (gettimeofday(&tv[0], NULL) < 0)
		err(84, "gettimeofday");
	tv[1].tv_sec = action->command->duration / game->freq;
	tv[1].tv_usec = (1000000 * (action->command->duration % game->freq)
		/ game->freq);
	timeradd(&action->start_time, &tv[1], &tv[2]);
	if (!timercmp(&tv[0], &tv[2], <)) {
		action->command->respond(game, player, action->argument);
		queue_pop(player->commands, &memory);
		if (player->commands->head)
			memcpy(&(action->start_time), &tv[0],
				sizeof(struct timeval));
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
