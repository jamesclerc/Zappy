/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** [enter description here]
*/

#include <stdio.h>

void send_pdr(FILE *stream, int id, int item_index)
{
	fprintf(stream, "pdr %i %i\n", id, item_index);
}

void send_pgt(FILE *stream, int id, int item_index)
{
	fprintf(stream, "pgt %i %i\n", id, item_index);
}

void send_rsp(FILE *stream, unsigned long int x, unsigned long int y,
	int item_index)
{
	fprintf(stream, "rsp %li %li %i\n", x, y, item_index);
}
