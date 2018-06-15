/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** egg notifications related functions
*/

#include <stdio.h>
#include "egg.h"

void send_neg(FILE *stream, egg_t *egg)
{
	if (stream)
		fprintf(stream, "%li %li %s %i\n",
		egg->pos.x, egg->pos.y, egg->team->name,
		egg->id);
}

void send_heg(FILE *stream, int egg_id)
{
	if (stream)
		fprintf(stream, "heg %i\n", egg_id);
}

void send_edi(FILE *stream, int egg_id)
{
	if (stream)
		fprintf(stream, "edi %i\n", egg_id);
}
