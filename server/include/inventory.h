/*
** EPITECH PROJECT, 2018
** inventory.h
** File description:
** Inventory
*/

#pragma once

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
