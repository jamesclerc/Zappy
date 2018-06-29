/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_fill.c
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "space.h"
#include "game.h"
#include "graphical_commands.h"

static bool check_underway_inc(list_t *incantations, int x, int y)
{
	list_t *tmp = incantations;
	incantation_t *inc;

	while (tmp) {
		inc = tmp->element;
		if (inc->participants[0]->entity.pos.x == (unsigned int )x &&
			inc->participants[0]->entity.pos.y == (unsigned int)y)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

static void fill_ressource(FILE *stream, game_t *game, int percent, int index)
{
	int ressource = game->map->height * game->map->width * ((float)percent / 100.0);
	int x = 0;
	int j;
	int i;

	if (index < 0 || index > 6)
		return;
	for (unsigned long i = 0; i < game->map->height; i++)
		for (unsigned long j = 0; j < game->map->width; j++)
			x = x + ((int *)(&game->map->cells[i][j]))[index];
	while (x < ressource) {
		i = rand() % game->map->height;
		j = rand() % game->map->width;
		if (((int *)(&game->map->cells[i][j]))[index] < 4 &&
			check_underway_inc(game->incantations, j, i)) {
			(((int *)(&game->map->cells[i][j])))[index] += 1;
			send_rsp(stream, j, i, index);
			x++;
		}
	}
}

void map_fill(FILE *stream, game_t *game)
{
	fill_ressource(stream, game, 30, 0);
	fill_ressource(stream, game, 20, 1);
	fill_ressource(stream, game, 20, 2);
	fill_ressource(stream, game, 20, 3);
	fill_ressource(stream, game, 15, 4);
	fill_ressource(stream, game, 12, 5);
	fill_ressource(stream, game, 5, 6);
}
