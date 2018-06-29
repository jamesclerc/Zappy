/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Client exit related functions
*/

#include "graphical_commands.h"
#include "containers.h"
#include "entity.h"
#include "game.h"

/// Removes a player from the list of players
//  `list_t *players`: the adress of the list_t *players pointer in game_t
//  `player_t *to_remove`: the adress of the player to be removed
void player_remove(list_t **players, player_t *to_remove)
{
	list_t *tmp = *players;
	player_t *pl;

	while (tmp) {
		pl = (player_t *)tmp->element;
		if (pl == to_remove) {
			pl = list_remove((*players == tmp) ? players : &tmp);
			player_destroy(pl);
			return;
		}
		tmp = tmp->next;
	}
	return;
}

/// Handles the disconnection of a client
bool disconnect_handle(game_t *game, struct epoll_event *ev, int efd)
{
	list_t *tmp;
	player_t *player;

	if (game->graph_stream && ev->data.fd == fileno(game->graph_stream)) {
		epoll_ctl(efd, EPOLL_CTL_DEL, fileno(game->graph_stream), NULL);
		fclose(game->graph_stream);
		game->graph_stream = NULL;
		return (true);
	}
	tmp = game->players;
	while (tmp) {
		player = (player_t *)tmp->element;
		if (player->fd == ev->data.fd) {
			list_remove((tmp == game->players) ?
				&game->players : &tmp);
			epoll_ctl(efd, EPOLL_CTL_DEL, player->fd, NULL);
			send_pdi(game->graph_stream, player->id);
			player_destroy(player);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}
