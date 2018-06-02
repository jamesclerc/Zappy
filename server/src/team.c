/*
** EPITECH PROJECT, 2018
** team.c
** File description:
** function
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "team.h"

team_t *parse_teams(int ac, char **av, int i, int slots)
{
	team_t *teams = NULL;
	int count = 0;

	while (i < ac && av[i][0] != '-') {
		teams = realloc(teams, sizeof(team_t) * (count + 2));
		if (teams == NULL)
			return (NULL);
		teams[count].name = av[i];
		teams[count].slots = slots;
		teams[count++].nb_max_lvl = 0;
	}
	memset(&(teams[count]), 0, sizeof(team_t));
	return (teams);
}
