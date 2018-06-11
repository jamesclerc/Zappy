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
	bool (*respond)(game_t *, player_t *, char *);
};

struct action_s {
	struct timeval start_time;
	command_t *command;
	char *argument;
};

bool queue_action(game_t *, player_t *, command_t *);
void execute_commands(game_t *);
bool respond_left(game_t *, player_t *, char *);
bool respond_right(game_t *, player_t *, char *);
bool respond_forward(game_t *, player_t *, char *);
bool respond_inventory(game_t *, player_t *, char *);
bool respond_connect_nbr(game_t *, player_t *, char *);
bool respond_broadcast(game_t *, player_t *, char *);
bool respond_look(game_t *, player_t *, char *);
bool respond_take(game_t *, player_t *, char *);
bool respond_set(game_t *, player_t *, char *);
bool handle_incantation(game_t *, player_t *, char *);
bool respond_incantation(game_t *, player_t *, char *);

// Testing
bool handle_pos(game_t *, player_t *, char *);
