/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Space-related Structures
*/

#include <stdlib.h>
#include "space.h"

/// Destroys a map created with `map_create`
void map_destroy(map_t *map)
{
	if (map == NULL)
		return;
	if (map->cells == NULL) {
		free(map);
		return;
	}
	for (unsigned long y = 0; y < map->height; y++)
		if (map->cells[y] != NULL)
			free(map->cells[y]);
	free(map->cells);
	free(map);
}

/// Creates a rectangular map of the given dimensions
map_t *map_create(unsigned long width, unsigned long height)
{
	map_t *map = malloc(sizeof(map_t));

	if (map == NULL)
		return (NULL);
	map->width = width;
	map->height = height;
	map->cells = calloc(height, sizeof(inventory_t *));
	if (map->cells == NULL) {
		map_destroy(map);
		return (NULL);
	}
	for (unsigned long y = 0; y < height; y++) {
		map->cells[y] = calloc(width, sizeof(inventory_t));
		if (map->cells[y] == NULL) {
			map_destroy(map);
			return (NULL);
		}
	}
	return (map);
}

/// Access a given cell of the map, wrapping included
inventory_t *map_peek(map_t *map, position_t *position)
{
	unsigned long x;
	unsigned long y;

	if (map == NULL || position == NULL)
		return (NULL);
	x = position->x % map->width;
	y = position->y % map->height;
	if (map->cells && map->cells[y])
		return (&(map->cells[y][x]));
	return (NULL);
}
