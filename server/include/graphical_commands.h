/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** graphical_commands header_files
*/

#pragma once
#include <stdbool.h>
#include "egg.h"
#include "incantation.h"
#include "game.h"
#include "space.h"

typedef struct graph_command_s graph_command_t;

struct graph_command_s {
	char *name;
	bool (*handle)(game_t *game, char *arguments);
};

bool get_graph_message(game_t *);
bool handle_pin(game_t *game, char *arguments);
bool handle_tst(game_t *game, char *arguments);
void graphical_protocol_init(game_t *);
void send_pnw(FILE *, player_t *);
void send_rsp(FILE *, int x, int y, int ressource_index);
void send_pdr(FILE *, int player_nb, int ressource_index);
void send_pgt(FILE *, int player_nb, int ressource_index);
void send_pet(FILE *, int player_nb);
void send_pmf(FILE *, int player_nb);
void send_ptu(FILE *, int player_nb, direction_t dir);
void send_pex(FILE *, int player_nb);
void send_pcb(FILE *, int player_nb, char *broadcast);
void send_pic(FILE *, incantation_t *);
void send_pie(FILE *, int player_nb, bool result);
void send_neg(FILE *, egg_t *egg);
void send_heg(FILE *, int egg_nb);
void send_edi(FILE *, int egg_nb);
void send_pdi(FILE *, int player_nb);
void send_seg(FILE *);
