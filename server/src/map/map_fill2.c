/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_fill2.c
*/

#include "map.h"

void fill_phiras(map_t *map, int percent)
{
        int ressource = map->height * map->width * percent / 100;
        int x = 0;
        int i;
        int j;

	for (unsigned long i = 0; i < map->height; i++)
                for (unsigned long j = 0; j < map->width; j++)
                        x = x + map->cells[i][j].phiras;
        while (x < ressource) {
                i = rand() % map->height;
                j = rand() % map->width;
                if (map->cells[i][j].phiras < 4) {
			map->cells[i][j].phiras += 1;
                        x++;
                }
        }
}

void fill_thystame(map_t *map, int percent)
{
        int ressource = map->height * map->width * percent / 100;
        int x = 0;
        int i;
        int j;

	for (unsigned long i = 0; i < map->height; i++)
                for (unsigned long j = 0; j < map->width; j++)
                        x = x + map->cells[i][j].thystame;
        while (x < ressource) {
                i = rand() % map->height;
                j = rand() % map->width;
                if (map->cells[i][j].thystame < 4) {
			map->cells[i][j].thystame += 1;
                        x++;
                }
        }
}

