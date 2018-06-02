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

struct position_t
{
	unsigned long x;
	unsigned long y;
};

inline direction_t direction_left(direction_t);
inline direction_t direction_right(direction_t);
inline position_t position_nudge(position_t, direction_t);
