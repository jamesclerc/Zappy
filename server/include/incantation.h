/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Incantaion header file
*/

#pragma once
#include "game.h"
#include "space.h"
#include "entity.h"

typedef struct incantation_s incantation_t;

struct incantation_s {
	bool actions_queued;
	player_t *participants[6];
};

void incantations_check(game_t *game);
void incantation_send(incantation_t *);
