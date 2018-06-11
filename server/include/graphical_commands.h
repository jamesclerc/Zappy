/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** graphical_commands header_files
*/

#pragma once
#include "game.h"

typedef struct graph_command_s graph_command_t;

struct graph_command_s {
	char *name;
	bool (*handle)(game_t *game, char *arguments);
};

bool get_graph_message(game_t *);
