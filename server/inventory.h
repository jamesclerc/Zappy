/*
** EPITECH PROJECT, 2018
** inventory.h
** File description:
** Inventory
*/

#ifndef INVENTORY_H_
# define INVENTORY_H_

#include <stdbool.h>

typedef struct inventory_s {
	int linemate;
	int deraumere;
	int sibur;
	int mendiane;
	int phiras;
	int thystame;
	int food;
} inventory_t;

bool inventory_has(inventory_t *a, inventory_t *b);

#endif /* !INVENTORY_H_ */
