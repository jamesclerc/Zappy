/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command handlers header
*/

#pragma once
#include <sys/time.h>
#include "entity.h"
#include "game.h"

typedef struct command_s command_t;
typedef struct action_s action_t;

struct command_s {
	char *name;
	int duration;
	void (*handle)(game_t *, player_t *, char *argument);
	void (*respond)(game_t *, player_t *, char *argument);
};

struct action_s {
	struct timeval start_time;
	command_t *command;
	char *argument;
};
