/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command handlers header
*/

#pragma once
#include <sys/time.h>
#include <stdbool.h>
#include "entity.h"
#include "game.h"

typedef struct command_s command_t;
typedef struct action_s action_t;

struct command_s {
	char *name;
	int duration;
	bool (*handle)(game_t *, player_t *, char *);
	void (*respond)(game_t *, player_t *, char *);
};

struct action_s {
	struct timeval start_time;
	command_t *command;
	char *argument;
};

bool handle_left(game_t *, player_t *, char *);
void respond_left(game_t *, player_t *, char *);
bool handle_right(game_t *, player_t *, char *);
void respond_right(game_t *, player_t *, char *);
