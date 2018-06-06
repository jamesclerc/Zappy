/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Client disconnection header file
*/

#pragma once
#include "containers.h"
#include "entity.h"
#include "game.h"

void player_remove(list_t **players, player_t *to_remove);
bool disconnect_handle(game_t *, struct epoll_event *);
