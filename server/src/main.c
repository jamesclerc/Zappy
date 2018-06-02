/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Server Entrypoint
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printUsage(char *av0, int exit_value)
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
	if (ac >= 2 && (strcasecmp(av[1], "-h") == 0
		|| strcasecmp(av[1], "-help") == 0))
		printUsage(av[0], 0);
	if (ac < 12)
		printUsage(av[0], 84);
	return (0);
}
