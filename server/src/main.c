/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Server Entrypoint
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "loop.h"
#include "game.h"
#include "parse.h"

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

int main(int ac, char **av)
{
	int args[5];
	game_t game;

	if (ac >= 2 && (strcasecmp(av[1], "-h") == 0
		|| strcasecmp(av[1], "-help") == 0))
		print_usage(av[0], 0);
	game.teams = parse_arguments(ac, av, args);
	if (!game.teams || game.teams[0].slots != 0)
		return (84);
	game.map = create_map(args[1], args[2]);
	if (!game.map)
		err(84, "malloc");
	if (!serv(&game, args))
		return (84);
	return (0);
}
