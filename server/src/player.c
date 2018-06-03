/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player Handling
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "entity.h"

player_t *player_create(int fd)
{
	player_t *new = malloc(sizeof(player_t));

	if (!new)
		return (NULL);
	memset(new, 0, sizeof(player_t));
	new->fd = fd;
	new->stream = fdopen(fd, "r+");
	if (!new->stream) {
		free(new);
		close(fd);
		return (NULL);
	}
	return (new);
}
