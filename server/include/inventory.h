/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Inventory Handling
*/

#pragma once
#include <stdbool.h>

typedef struct inventory_s inventory_t;

struct inventory_s
{
	int food;
	int linemate;
	int deraumere;
	int sibur;
	int mendiane;
	int phiras;
	int thystame;
};

bool inventory_has(inventory_t *haystack, inventory_t *needle);
bool inventory_take(inventory_t *source, inventory_t *amount);
void inventory_give(inventory_t *destination, inventory_t *amount);
void inventory_move(inventory_t *destination, inventory_t *source);
bool inventory_check_inc(inventory_t *inventory, inventory_t *required);

extern const inventory_t elevations[8];
extern const char *item_names[8];
