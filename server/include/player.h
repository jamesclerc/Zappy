/*
** EPITECH PROJECT, 2018
** player.h
** File description:
** player header
*/

#pragma once

#include "inventory.h"
#include "direction.h"
#include "handler.h"
#include "containers.h"

typedef struct player_s player_t;
typedef struct game_state_s game_state_t;

struct game_state_s {
	inventory_t inventory;
	int x;
	int y;
	int level;
	direction_t direction;
};

struct player_s {
	game_state_t info;
	FILE *fs;
	queue_t *cmd_queue;
	team_t *team;
};
