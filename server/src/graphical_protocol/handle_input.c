/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Graphical client commands handling
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphical_commands.h"
#include "game.h"

static graph_command_t graph_commands[] = {
	{"msz", &handle_msz},
	{"bct", &handle_bct},
	{"mct", &handle_mct},
	{"tna", &handle_tna},
	{"ppo", &handle_ppo},
	{"plv", &handle_plv},
	{"pin", &handle_pin},
	{"sgt", NULL},
	{"sst", NULL},
	{NULL, NULL}
};

static bool choose_command(game_t *game, char *cmd)
{
	int i = -1;

	while (graph_commands[++i].name) {
		if (strcasecmp(graph_commands[i].name, cmd) == 0)
			break;
	}
	if (!graph_commands[i].name ||
		!graph_commands[i].handle(game, strtok(NULL, ""))) {
		fprintf(game->graph_stream, "ko\n");
		return (false);
	}
	return (true);
}

bool get_graph_message(game_t *game)
{
	char *message = NULL;
	size_t i = 0;
	bool ret;

	if (game->graph_stream == NULL)
		return (false);
	if (getline(&message, &i, game->graph_stream) == -1) {
		fclose(game->graph_stream);
		return (false);
	}
	if (message == NULL)
		return (false);
	message[strcspn(message, "\r\n")] = '\0';
	if (strlen(message) == 0) {
		free(message);
		return (true);
	}
	message = strtok(message, " ");
	ret = choose_command(game, message);
	free(message);
	return (ret);
}
