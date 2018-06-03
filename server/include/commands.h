/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command handlers header
*/

#pragma once
#include <time.h>
#include "entity.h"
#include "game.h"

typedef struct command_s command_t;
typedef struct action_s action_t;

struct command_s {
	char *name;
	int duration;
	void (*handle)(game_t *, player_t *, void **data);
	void (*respond)(game_t *, player_t *, void *data);
};

struct action_s {
	time_t start_time;
	command_t *cmd;
	void *data;
};
