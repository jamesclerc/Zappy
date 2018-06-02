/*
** EPITECH PROJECT, 2018
** player.h
** File description:
** player header
*/

#ifndef PLAYER_H_
# define PLAYER_H_

#include "inventory.h"
#include "direction.h"
#include "handler.h"
#include "containers.h"

typedef struct player_s {
	inventory_t inventory;
	int x;
	int y;
	int id;
	FILE *fs;
	int level;
	Direction direction;
	queue_t *cmd_queue;
} player_t;

#endif /* !PLAYER_H_ */
