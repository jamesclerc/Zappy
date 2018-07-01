/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** incantation message sending
*/

#include <stdio.h>
#include "incantation.h"

void incantation_send(incantation_t *inc)
{
	int i = 0;

	while (i < 6 && inc->participants[i]) {
		fprintf(inc->participants[i]->stream, "Elevation underway\n");
		i++;
	}
}
