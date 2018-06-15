/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** pnw notification related functions
*/

#include <stdio.h>
#include "entity.h"

void send_pnw(FILE *stream, player_t *player)
{
	int tmp;

	if (!stream)
		return;
	if (player->entity.facing % 4 == 0)
		tmp = player->entity.facing / 2 + 1;
	else
		tmp = player->entity.facing % 6 + 2;
	fprintf(stream, "pnw %li %li %i %i %s ",
		player->entity.pos.x, player->entity.pos.y, tmp,
		player->entity.level, player->entity.team->name);
	for (unsigned int i = 0; i < 7; i++)
		fprintf(stream, " %i", ((int *)player)[i]);
	fprintf(stream, "\n");
}
