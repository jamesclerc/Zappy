/*
** EPITECH PROJECT, 2018
** player.h
** File description:
** player header
*/

#pragma once

#include <stddef.h>
#include "inventory.h"
#include "direction.h"
#include "handler.h"
#include "containers.h"

typedef struct player_s player_t;
typedef struct entity_s entity_t;
typedef struct position_s position_t;

struct position_s {
	size_t x;
	size_t y;
};

struct entity_s {
	inventory_t inventory;
	direction_t facing;
	position_t pos;
	team_t *team;
	short level;
}

struct player_s {
	entity_t entity;
	int fd;
	FILE *steam;
	queue_t *commands;
};
