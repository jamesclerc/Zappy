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
	setlinebuf(new->stream);
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

/// Destroy a player
void player_destroy(player_t *player)
{
	while (player->commands->head)
		queue_pop(player->commands, NULL);
	queue_destroy(player->commands);
	fclose(player->stream);
	free(player);
}

/// Searches the team and links the player to it
//  `team_t *teams`: the team_t array created by team_get_names
//  `player_t *player`: the player giving the name of his team_t
//  `char *team_name`: the name of the team asked by the player
//  `bool return`: returns wether the team was found and linked or not
bool link_player_team(team_t *teams, player_t *player, char *team_name)
{
	int i = -1;

	while (teams[++i].name) {
		if (strcmp(team_name, teams[i].name) == 0) {
			player->entity.team = &teams[i];
			return (true);
		}
	}
	return (false);
}
