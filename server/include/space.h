/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Space-related structures
*/

#pragma once

typedef enum direction_e direction_t;
typedef struct position_s position_t;

enum direction_e
{
	DIR_NORTH = 0,
	DIR_NORTHEAST,
	DIR_EAST,
	DIR_SOUTHEAST,
	DIR_SOUTH,
	DIR_SOUTHWEST,
	DIR_WEST,
	DIR_NORTHWEST,
	DIR_COUNT,
};

struct position_s
{
	unsigned long x;
	unsigned long y;
};

static inline direction_t direction_left(direction_t dir)
{
	if (dir < 2)
		dir += DIR_COUNT;
	return (dir - 2);
}

static inline direction_t direction_right(direction_t dir)
{
	return ((dir + 2) % DIR_COUNT);
}
