/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Food units updating related functions
*/

#include "containers.h"
#include "entity.h"

static void food_take(list_t **tmp)
{
	player_t *player;

	player = (player_t *)(*tmp)->element;
	player->entity.inventory.food--;
	if (player->entity.inventory.food <= 0) {
		player = list_remove(tmp);
		fprintf(player->stream, "dead\n");
		player_destroy(player);
		return;
	}
	gettimeofday(&player->entity.last_meal, NULL);
}

void food_update(list_t **players, int freq)
{
	list_t *tmp = *players;
	player_t *player;
	struct timeval cur_time;
	struct timeval res;
	struct timeval one_food_time;

	one_food_time.tv_sec = 126 / freq;
	one_food_time.tv_usec = (1000000 * (126 % freq) / freq);
	gettimeofday(&cur_time, NULL);
	while (tmp) {
		player = (player_t *)tmp->element;
		timeradd(&player->entity.last_meal, &one_food_time, &res);
		if (!timercmp(&cur_time, &res, <)) {
			food_take((tmp == *players) ? players : &tmp);
			return;
		}
		tmp = tmp->next;
	}
}
