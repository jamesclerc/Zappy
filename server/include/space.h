/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Space-related Structures
*/

#pragma once
#include <stdio.h>
#include "inventory.h"

typedef enum direction_e direction_t;
typedef struct position_s position_t;
typedef struct map_s map_t;

enum direction_e
{
	DIR_NORTH = 0,
	DIR_NORTHWEST,
	DIR_WEST,
	DIR_SOUTHWEST,
	DIR_SOUTH,
	DIR_SOUTHEAST,
	DIR_EAST,
	DIR_NORTHEAST,
	DIR_COUNT,
};

struct position_s
{
	unsigned long x;
	unsigned long y;
};

struct map_s
{
	inventory_t **cells;
	unsigned long height;
	unsigned long width;
};

map_t *map_create(unsigned long width, unsigned long height);
void map_destroy(map_t *);
inventory_t *map_peek(map_t *, position_t *);
void position_nudge(map_t *map, position_t *pos, direction_t dir);

static inline direction_t direction_left(direction_t dir)
{
	return ((dir + 2) % DIR_COUNT);
}

static inline direction_t direction_right(direction_t dir)
{
	if (dir < 2)
		dir += DIR_COUNT;
	return (dir - 2);
}
