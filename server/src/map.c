/*
** EPITECH PROJECT, 2018
** map.c
** File description:
** Map related functions
*/

#include <stdlib.h>
#include <string.h>
#include "map.h"

map_t *create_map(int width, int height)
{
	int i = -1;
	map_t *map = malloc(sizeof(map_t));

	if(!map)
		return (NULL);
	map->data = malloc(sizeof(inventory_t*) * height);
	while (++i < height) {
		map->data[i] = malloc(sizeof(inventory_t) * width);
		if (!map->data[i])
			return (NULL);
		memset(map->data[i], 0, sizeof(inventory_t) * width);
	}
	return (map);
}
