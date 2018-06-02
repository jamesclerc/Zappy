/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Server Entrypoint
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <err.h>
#include "map.h"
#include "team.h"
#include "loop.h"

void print_usage(char *av0, int exit_value)
{
	printf("USAGE: %s -p port -x width -y height -n name1 name2 ... -c "
		"clientNb -f freq\n\tport\t\tis the port number\n\twidth\t\tis "
		"the width of the world\n\theight\t\tis the height of the world"
		"\n\tnameX\t\tis the name of the team X\n\tclientsNb\tis the "
		"number of authorized clients per team\n\tfreq\t\tis the reciproc"
		"al of time unit for execution of actions\n", av0);
	exit(exit_value);

}

int check_number(char *av0, char *arg)
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

int find_arg(int ac, char **av, char *opt)
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

int main(int ac, char **av)
{
	int args[5];
	map_t *map;
	team_t *teams;

	if (ac >= 2 && (strcasecmp(av[1], "-h") == 0
		|| strcasecmp(av[1], "-help") == 0))
		print_usage(av[0], 0);
	if (ac < 14)
		print_usage(av[0], 84);
	teams = parse_arguments(ac, av, args);
	if (!teams || teams[0].slots != 0)
		return (84);
	map = create_map(args[1], args[2]);
	if (!map)
		err(84, "malloc");
	if (!init_loop(map, teams, args))
		return (84);
	return (0);
}
