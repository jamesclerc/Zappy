/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_fill.c
*/

#include <time.h>
#include <stdlib.h>
#include "space.h"

static void fill_ressource(map_t *map, int item_index, int percent)
{
	int ressource = map->height * map->width * percent / 100;
	int x = 0;
	int j;
	int i;

	if (item_index < 0 || item_index > 8)
		return;
	for (unsigned long i = 0; i < map->height; i++)
		for (unsigned long j = 0; j < map->width; j++)
			x = x + ((int *)(&map->cells[i][j]))[item_index];
	while (x < ressource) {
		i = rand() % map->height;
		j = rand() % map->width;
		if (((int *)(&map->cells[i][j]))[item_index] < 4) {
			(((int *)(&map->cells[i][j])))[item_index] += 1;
			x++;
		}
	}
}

void map_fill(map_t *map) {
	fill_ressource(map, 50, 1);
	fill_ressource(map, 50, 2);
	fill_ressource(map, 50, 3);
	fill_ressource(map, 40, 4);
	fill_ressource(map, 30, 5);
	fill_ressource(map, 30, 6);
	fill_ressource(map, 10, 7);
}
