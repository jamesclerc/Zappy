/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Egg representation header
*/

#pragma once
#include <sys/time.h>
#include "space.h"
#include "team.h"
#include "containers.h"

#define EGG_LAYING_TIME 300

typedef struct egg_s egg_t;

struct egg_s {
	position_t pos;
	team_t *team;
	struct timeval laying_time;
};

void hatch_egg(game_t *);
