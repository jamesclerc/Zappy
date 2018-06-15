/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Fork command related functions
*/

#include <sys/time.h>
#include <stdlib.h>
#include "game.h"
#include "entity.h"
#include "egg.h"
#include "graphical_commands.h"

static int egg_id = 0;

void hatch_egg(game_t *game)
{
	struct timeval tv[3];
	egg_t *egg;
	egg_t *memory;

	if (!game->hatching_eggs->tail || !game->hatching_eggs->head)
		return;
	egg = (egg_t *)game->hatching_eggs->tail->element;
	gettimeofday(&tv[0], NULL);
	tv[1].tv_sec = EGG_LAYING_TIME / game->freq;
	tv[1].tv_usec = (1000000 * (EGG_LAYING_TIME % game->freq) / game->freq);
	timeradd(&egg->laying_time, &tv[1], &tv[2]);
	if (!timercmp(&tv[0], &tv[2], <)) {
		memory = malloc(sizeof(egg_t));
		if (!memory)
			return;
		queue_pop(game->hatching_eggs, memory);
		queue_push(memory->team->eggs, memory);
		send_heg(game->graph_stream, memory->id);
	}
}

bool respond_fork(game_t *game, player_t *player, char *argument)
{
	egg_t egg;

	if (argument) {
		fprintf(player->stream, "ko\n");
		return (true);
	}
	egg.pos = player->entity.pos;
	gettimeofday(&egg.laying_time, NULL);
	egg.team = player->entity.team;
	egg.id = ++egg_id;
	queue_push(game->hatching_eggs, &egg);
	fprintf(player->stream, "ok\n");
	send_neg(game->graph_stream, &egg);
	return (true);
}

bool handle_fork(game_t *game, player_t *player, char *argument)
{
	(void)game;
	if (argument) {
		fprintf(player->stream, "ko\n");
		return (true);
	}
	return (true);
}
