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
#include "graphical_commands.h"

static void fill_ressource(FILE *stream, map_t *map, int percent, int index)
{
	int ressource = map->height * map->width * ((float)percent / 100.0);
	int x = 0;
	int j;
	int i;

	if (index < 0 || index > 6)
		return;
	for (unsigned long i = 0; i < map->height; i++)
		for (unsigned long j = 0; j < map->width; j++)
			x = x + ((int *)(&map->cells[i][j]))[index];
	while (x < ressource) {
		i = rand() % map->height;
		j = rand() % map->width;
		if (((int *)(&map->cells[i][j]))[index] < 4) {
			(((int *)(&map->cells[i][j])))[index] += 1;
			send_rsp(stream, j, i, index);
			x++;
		}
	}
}

void map_fill(FILE *stream, map_t *map)
{
	fill_ressource(stream, map, 30, 0);
	fill_ressource(stream, map, 20, 1);
	fill_ressource(stream, map, 20, 2);
	fill_ressource(stream, map, 20, 3);
	fill_ressource(stream, map, 15, 4);
	fill_ressource(stream, map, 12, 5);
	fill_ressource(stream, map, 5, 6);
}
