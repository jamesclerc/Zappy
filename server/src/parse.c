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

/// Checks that the given argument is a valid numeric value and retrun it
static int check_number(char *arg)
{
	int i = -1;
	int ret;

	while (arg[++i]) {
		if (!isdigit((int)arg[i]))
			return (-1);
	}
	ret = atoi(arg);
	return (ret);
}

/// finds the requested option following the given opt string (ex: "-h")
static int find_arg(int ac, char **av, char *opt)
{
	int i = 0;

	while (++i < ac - 1) {
		if (strcmp(av[i], opt) == 0)
			return (check_number(av[i + 1]));
	}
	return (-1);
}

/// parses all possible numeric program arguments
static void parse_numbers(int ac, char **av, int *args)
{
	args[3] = find_arg(ac, av, "-c");
	if (args[3] == -1)
		args[3] = 6;
	args[4] = find_arg(ac, av, "-f");
	if (args[4] == -1)
		args[4] = 100;
	args[0] = find_arg(ac, av, "-p");
	if (args[0] == -1)
		args[0] = 4242;
	args[1] = find_arg(ac, av, "-x");
	args[2] = find_arg(ac, av, "-y");
	if (args[1] == -1)
		args[1] = 16;
	if (args[2] == -1)
		args[2] = 16;
}

team_t *parse_arguments(int ac, char **av, int *args)
{
	int i = 0;

	parse_numbers(ac, av, args);
	while (++i < ac - 1) {
		if (strcmp(av[i], "-n") == 0)
			return (parse_teams(ac, av, ++i, args[3]));
	}
	print_usage(av[0], 84);
	return (NULL);
}
