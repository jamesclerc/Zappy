/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** player events notification functions
*/

#include <stdio.h>
#include "space.h"

void send_pmf(FILE *stream, int id)
{
	fprintf(stream, "pmf %i\n", id);
}

void send_ptu(FILE *stream, int id, direction_t dir)
{
	int tmp;

	if (dir % 4 == 0)
		tmp = dir / 2 + 1;
	else
		tmp = dir % 6 + 2;
	fprintf(stream, "ptu %i %i\n", id, tmp);
}

void send_pet(FILE *stream, int id)
{
	fprintf(stream, "pet %i\n", id);
}

void send_pex(FILE *stream, int id)
{
	fprintf(stream, "pex %i\n", id);
}

void send_pdi(FILE *stream, int id)
{
	fprintf(stream, "pdi %i\n", id);
}
