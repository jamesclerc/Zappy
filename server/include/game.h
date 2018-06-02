/*
** EPITECH PROJECT, 2018
** game.h
** File description:
** game_t header
*/

#pragma once

#include "containers.h"
#include "map.h"
#include "team.h"

typedef struct game_s {
	map_t *map;
	team_t *teams;
	list_t *players;
	int freq;
} game_t;
