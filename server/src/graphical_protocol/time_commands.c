/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Time unit related graphical commands related functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

bool handle_sst(game_t *game, char *arguments)
{
	int freq;

	if (!arguments || arguments[0] < '0' || arguments[0] > '9')
		return (false);
	freq = atoi(arguments);
	game->freq = freq;
	fprintf(game->graph_stream, "sst %i\n", game->freq);
	return (true);
}

bool handle_sgt(game_t *game, char *arguments)
{
	if (arguments)
		return (false);
	fprintf(game->graph_stream, "sgt %i\n", game->freq);
	return (true);
}
