/*
** EPITECH PROJECT, 2018
** parse.c
** File description:
** arguments parsing functions
*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "team.h"
#include "parse.h"

static int check_number(char *av0, char *arg)
{
	int i = -1;
	int ret;

	while (arg[++i]) {
		if (!isdigit((int)arg[i]))
			return (-1);
	}
	ret = atoi(arg);
	if (ret <= 0)
		print_usage(av0, 84);
	return (ret);
}

static int find_arg(int ac, char **av, char *opt)
{
	int i = 0;

	while (++i < ac - 1) {
		if (strcmp(av[i], opt) == 0)
			return (check_number(av[0], av[i + 1]));
	}
	print_usage(av[0], 84);
	return (-1);
}

team_t *parse_arguments(int ac, char **av, int *args)
{
	int i = 0;

	args[0] = find_arg(ac, av, "-p");
	args[1] = find_arg(ac, av, "-x");
	args[2] = find_arg(ac, av, "-y");
	args[3] = find_arg(ac, av, "-c");
	args[4] = find_arg(ac, av, "-f");
	while (++i < ac - 1) {
		if (strcmp(av[i], "-n") == 0)
			return (parse_teams(ac, av, ++i, args[3]));
	}
	return (NULL);
}
