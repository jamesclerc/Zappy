/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Incantaion header file
*/

#pragma once
#include "space.h"
#include "entity.h"

typedef struct incantation_s incantation_t;

struct incantation_s {
	position_t pos;
	bool actions_queued;
	player_t *participants[6];
};
