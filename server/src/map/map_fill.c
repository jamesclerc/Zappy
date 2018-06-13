/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_fill.c
*/

#include "space.h"
#include "map.h"

static void fill_linemate(map_t *map, int percent)
{
	int ressource = map->height * map->width * percent / 100;
	int x = 0;
	int i;
	int j;

	for (unsigned long i = 0; i < map->height; i++)
		for (unsigned long j = 0; j < map->width; j++)
			x = x + map->cells[i][j].linemate;
	while (x < ressource) {
		i = rand() % map->height;
		j = rand() % map->width;
		if (map->cells[i][j].linemate < 4) {
			map->cells[i][j].linemate += 1;
			x++;
		}
	}
}

static void fill_deraumere(map_t *map, int percent)
{
	int ressource = map->height * map->width * percent / 100;
	int x = 0;
	int i;
	int j;

	for (unsigned long i = 0; i < map->height; i++)
		for (unsigned long j = 0; j < map->width; j++)
			x = x + map->cells[i][j].deraumere;
	while (x < ressource) {
		i = rand() % map->height;
		j = rand() % map->width;
		if (map->cells[i][j].deraumere < 4) {
			map->cells[i][j].deraumere += 1;
			x++;
		}
	}
}

static void fill_sibur(map_t *map, int percent)
{
	int ressource = map->height * map->width * percent / 100;
	int x = 0;
	int i;
	int j;

	for (unsigned long i = 0; i < map->height; i++)
		for (unsigned long j = 0; j < map->width; j++)
			x = x + map->cells[i][j].sibur;
	while (x < ressource) {
		i = rand() % map->height;
		j = rand() % map->width;
		if (map->cells[i][j].sibur < 4) {
			map->cells[i][j].sibur += 1;
			x++;
		}
	}
}

static void fill_mendiane(map_t *map, int percent)
{
	int ressource = map->height * map->width * percent / 100;
	int x = 0;
	int i;
	int j;

	for (unsigned long i = 0; i < map->height; i++)
		for (unsigned long j = 0; j < map->width; j++)
			x = x + map->cells[i][j].mendiane;
	while (x < ressource) {
		i = rand() % map->height;
		j = rand() % map->width;
		if (map->cells[i][j].mendiane < 4) {
			map->cells[i][j].mendiane += 1;
			x++;
		}
	}
}

void fill_map(map_t *map) {
	srand(time(NULL));
	fill_linemate(map, 50);
	fill_deraumere(map, 50);
	fill_sibur(map, 40);
	fill_mendiane(map, 30);
	fill_phiras(map, 30);
	fill_thystame(map, 10);
}
