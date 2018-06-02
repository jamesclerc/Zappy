/*
** EPITECH PROJECT, 2018
** team.h
** File description:
** header
*/

#pragma once

#include <stddef.h>

typedef struct team_s {
	char *name;
	size_t slots;
	size_t nb_max_lvl;
} team_t;

team_t *parse_teams(int ac, char **av, int i, int slots);
