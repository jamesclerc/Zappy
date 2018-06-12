/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Map content commands related functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

bool handle_msz(game_t *game, char *arguments)
{
	if (arguments)
		return (false);
	fprintf(game->graph_stream, "msz %li %li\n", game->map->width,
		game->map->height);
	return (true);
}

static bool is_digits_only(char *str)
{
	int i = -1;

	while (str[++i]) {
		if (str[i] < '0' || str[i] > '9')
			return (false);
	}
	return (true);
}

static bool show_tile(game_t *game, int x, int y)
{
	int *cell;

	if (x < 0 || x >= (int)game->map->width || y < 0 ||
	y >= (int)game->map->height)
		return (false);
	cell = (int *)&game->map->cells[y][x];
	fprintf(game->graph_stream, "bct %i %i %i %i %i %i %i %i %i\n", x, y,
		cell[0], cell[1], cell[2], cell[3], cell[4], cell[5], cell[6]);
	return (true);
}

bool handle_bct(game_t *game, char *arguments)
{
	char *str_x = strtok(arguments, " ");
	char *str_y = strtok(NULL, " ");
	int x;
	int y;

	if (!arguments || !str_x || !str_y || !is_digits_only(str_x) ||
		!is_digits_only(str_y))
		return (false);
	x = atoi(str_x);
	y = atoi(str_y);
	return (show_tile(game, x, y));
}

bool handle_mct(game_t *game, char *arguments)
{
	int x;
	int y = -1;

	if (arguments)
		return (false);
	while (++y < (int)game->map->height) {
		x = -1;
		while (++x < (int)game->map->width)
			show_tile(game, x, y);
	}
	return (true);
}
