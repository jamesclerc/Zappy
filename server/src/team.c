/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** function
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "entity.h"
#include "team.h"
#include "game.h"
#include "containers.h"
#include "egg.h"

/// Extract all team names from program arguments
team_t *team_get_names(char *av[], int start, int slots)
{
	team_t *teams = NULL;
	queue_t *queue;
	int count = 0;

	for (; av[start] != NULL && av[start][0] != '-'; start++) {
		teams = realloc(teams, (count + 2) * sizeof(team_t));
		queue = queue_create(sizeof(egg_t));
		teams[count++] = (team_t) {av[start], slots, 0, queue};
	}
	memset(teams + count, 0, sizeof(team_t));
	return (teams);
}

/// Destroys a team_t array created by team_get_names
void teams_destroy(team_t *teams)
{
	int i = 0;

	while (teams[i].name != NULL) {
		queue_destroy(teams[i].eggs);
		free(teams[i].name);
	}
	free(teams);
}

static void remove_graph_from_players(game_t *game, player_t *graph)
{
	list_t *tmp = game->players;

	while (tmp) {
		if (tmp->element == graph)
			list_remove((tmp == game->players) ?
				&game->players : &tmp);
		tmp = tmp->next;
	}
}

static void init_player_in_team(team_t *team, player_t *player)
{
	egg_t memory;

	if (team->slots == 0 && team->eggs->head) {
		queue_pop(team->eggs, &memory);
		player->entity.pos.x = memory.pos.x;
		player->entity.pos.y = memory.pos.y;
	} else if (team->slots > 0)
		team->slots--;
	gettimeofday(&player->entity.last_meal, NULL);
	player->entity.team = team;
}

/// Searches the team and links the player to it
//  `team_t *teams`: the team_t array created by team_get_names
//  `player_t *player`: the player giving the name of his team_t
//  `char *team_name`: the name of the team asked by the player
//  `bool return`: returns wether the team was found and linked or not
bool link_player_team(game_t *game, player_t *player, char *team_name)
{
	int i = -1;

	while (game->teams[++i].name) {
		if (strcmp(team_name, game->teams[i].name) == 0 &&
			((game->teams[i].slots > 0) ||
			game->teams[i].eggs->head)) {
			init_player_in_team(&game->teams[i], player);
			return (true);
		}
	}
	if (strcmp(team_name, "GRAPHIC") == 0 && game->graph_stream == NULL) {
		remove_graph_from_players(game, player);
		queue_destroy(player->commands);
		game->graph_stream = player->stream;
		free(player);
		return (false);
	}
	fprintf(player->stream, "ko\n");
	return (false);
}
