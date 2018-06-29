/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Entity Handling
*/

#pragma once
#include <stdio.h>
#include <sys/time.h>
#include "containers.h"
#include "inventory.h"
#include "space.h"
#include "team.h"
#include "game.h"

typedef struct entity_s entity_t;
typedef struct player_s player_t;

struct entity_s
{
	inventory_t inventory;
	direction_t facing;
	position_t pos;
	team_t *team;
	short level;
	struct timeval last_meal;
};

struct player_s
{
	entity_t entity;
	FILE *stream;
	int fd;
	unsigned int id;
	queue_t *commands;
};

player_t *player_create(int fd);
void player_destroy(player_t *);
player_t *player_by_fd(list_t *list, int fd);
bool link_player_team(game_t *teams, player_t *player, char *team_name);
