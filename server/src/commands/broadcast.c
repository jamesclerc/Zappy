/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Broadcast command related functions
*/

#include "space.h"
#include "game.h"
#include "entity.h"
#include "graphical_commands.h"

static int origin_resolve(unsigned int *dist, direction_t horizontal_dir,
	direction_t vertical_dir, direction_t to_dir)
{
	direction_t brute_dir;
	int res;

	if (dist[0] == dist[1]
		&& ((vertical_dir == DIR_NORTH && horizontal_dir == DIR_WEST)
		|| (vertical_dir == DIR_SOUTH && horizontal_dir == DIR_EAST)))
		brute_dir = vertical_dir + 1;
	else if (dist[0] == dist[1])
		brute_dir = vertical_dir - 1;
	else
		brute_dir = (dist[0] > dist[1]) ? horizontal_dir : vertical_dir;
	res = brute_dir - to_dir;
	if (res < 0)
		res += DIR_COUNT;
	return (res + 1);
}

static int broadcast_origin(map_t *map, entity_t *from, entity_t *to)
{
	unsigned int dist[2] = {(to->pos.x > from->pos.x) ?
		to->pos.x - from->pos.x : from->pos.x - to->pos.x,
		(to->pos.y > from->pos.y) ? to->pos.y - from->pos.y
			: from->pos.y - to->pos.y};
	direction_t horizontal_dir = (to->pos.x > from->pos.x)
		? DIR_WEST : DIR_EAST;
	direction_t vertical_dir = (to->pos.y > from->pos.y)
		? DIR_NORTH : DIR_SOUTH;

	if (dist[0] == 0 && dist[1] == 0)
		return (0);
	if (map->width - dist[0] < dist[0]) {
		dist[0] = map->width - dist[0];
		horizontal_dir = (horizontal_dir + 4) % DIR_COUNT;
	}
	if (map->height - dist[1] < dist[1]) {
		dist[1] = map->height - dist[1];
		vertical_dir = (vertical_dir + 4) % DIR_COUNT;
	}
	return (origin_resolve(dist, horizontal_dir, vertical_dir, to->facing));
}

bool respond_broadcast(game_t *game, player_t *player, char *argument)
{
	list_t *tmp = game->players;

	if (!argument)
		return (false);
	send_pbc(game->graph_stream, player->fd, argument);
	while (tmp) {
		if (tmp->element != player
			&& ((player_t *)tmp->element)->entity.team != NULL)
			fprintf(((player_t *)tmp->element)->stream,
				"message %i, %s\n",
				broadcast_origin(game->map, &player->entity,
					&(((player_t *)tmp->element)->entity)),
					argument);
		tmp = tmp->next;
	}
	return (true);
}
