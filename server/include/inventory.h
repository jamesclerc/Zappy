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
	int food;
	int linemate;
	int deraumere;
	int sibur;
	int mendiane;
	int phiras;
	int thystame;
} inventory_t;

bool inventory_has(inventory_t *to_compare, inventory_t *reference);

#endif /* !INVENTORY_H_ */
