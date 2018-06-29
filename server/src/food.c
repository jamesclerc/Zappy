/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Food units updating related functions
*/

#include <stdio.h>
#include "containers.h"
#include "entity.h"
#include "graphical_commands.h"

static void food_take(FILE *stream, list_t **tmp, int efd)
{
	player_t *player;

	player = (player_t *)(*tmp)->element;
	player->entity.inventory.food--;
	send_pet(stream, player->fd);
	if (player->entity.inventory.food <= 0) {
		player = list_remove(tmp);
		fprintf(player->stream, "dead\n");
		send_pdi(stream, player->fd);
		epoll_ctl(efd, EPOLL_CTL_DEL, player->fd, NULL);
		player_destroy(player);
		return;
	}
	gettimeofday(&player->entity.last_meal, NULL);
}

void food_update(FILE *stream, list_t **players, int freq, int efd)
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
		if (player->entity.team && !timercmp(&cur_time, &res, <)) {
			food_take(stream, (tmp == *players) ? players : &tmp,
				efd);
			return;
		}
		tmp = tmp->next;
	}
}
