/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Divers events notification functions
*/

#include <stdio.h>

void send_pbc(FILE *stream, int id, char *message)
{
	fprintf(stream, "pbc %i %s\n", id , message);
}
