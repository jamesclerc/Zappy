/*
** EPITECH PROJECT, 2018
** team.h
** File description:
** header
*/

#pragma once
#include <stddef.h>

typedef struct team_s team_t;

struct team_s
{
	char *name;
	size_t slots;
	size_t overlords;
};

team_t *team_get_names(char *av[], int start, int slots);
