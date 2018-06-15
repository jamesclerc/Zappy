/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Incantation notifications functions
*/

#include <stdio.h>
#include "incantation.h"

void send_pic(FILE *stream, incantation_t *inc)
{
	player_t *tmp = inc->participants[0];
	int i = 0;

	fprintf(stream, "pic %i", tmp->fd);
	while (++i < 6 && inc->participants[i])
		fprintf(stream, " %i", inc->participants[i]->fd);
	fprintf(stream, "\n");
}

void send_pie(FILE *stream, int id, bool result)
{
	fprintf(stream, "pie %i %s", id, (result) ? "ok" : "ko");
}
