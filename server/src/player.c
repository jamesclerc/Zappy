/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player Handling
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "containers.h"
#include "entity.h"
#include "commands.h"

/// Create a player from a file descriptor
player_t *player_create(int fd)
{
	player_t *new = malloc(sizeof(player_t));

	if (!new)
		return (NULL);
	memset(new, 0, sizeof(player_t));
	new->fd = fd;
	new->commands = queue_create(sizeof(action_t));
	if (!new->commands) {
		free(new);
		return (NULL);
	}
	new->stream = fdopen(fd, "r+");
	if (!new->stream) {
		free(new);
		close(fd);
		return (NULL);
	}
	return (new);
}

/// Find a player in a linked list by its file descriptor
player_t *player_by_fd(list_t *list, int fd)
{
	if (list == NULL)
		return (NULL);
	while (list != NULL && list->element != NULL
		&& ((player_t *) list->element)->fd != fd)
		list = list->next;
	return (list->element);
}
