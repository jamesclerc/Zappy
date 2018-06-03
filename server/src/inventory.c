/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Inventory Handling
*/

#include <stddef.h>
#include "inventory.h"

const inventory_t elevations[8] = {
	{0, 1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0, 0},
	{0, 2, 0, 1, 0, 2, 0},
	{0, 1, 1, 2, 0, 1, 0},
	{0, 1, 2, 1, 3, 0, 0},
	{0, 1, 2, 3, 0, 1, 0},
	{0, 2, 2, 2, 2, 2, 1},
	{0, 0, 0, 0, 0, 0, 0}
};

/// Checks whether an inventory contains everyting another has
//  `bool return`: Is the needle found in haystack?
bool inventory_has(inventory_t *haystack, inventory_t *needle)
{
	if (haystack == NULL || needle == NULL)
		return (false);
	return (haystack->linemate >= needle->linemate
		&& haystack->deraumere >= needle->deraumere
		&& haystack->sibur >= needle->sibur
		&& haystack->mendiane >= needle->mendiane
		&& haystack->phiras >= needle->phiras
		&& haystack->thystame >= needle->thystame
		&& haystack->food >= needle->food);
}

/// Takes a given amount from an inventory
bool inventory_take(inventory_t *source, inventory_t *amount)
{
	if (source == NULL || amount == NULL ||!inventory_has(source, amount))
		return (false);
	source->linemate -= amount->linemate;
	source->deraumere -= amount->deraumere;
	source->sibur -= amount->sibur;
	source->mendiane -= amount->mendiane;
	source->phiras -= amount->phiras;
	source->thystame -= amount->thystame;
	source->food -= amount->food;
	return (true);
}

/// Gives a given amount to an inventory
void inventory_give(inventory_t *destination, inventory_t *amount)
{
	if (destination == NULL || amount == NULL)
		return;
	destination->linemate += amount->linemate;
	destination->deraumere += amount->deraumere;
	destination->sibur += amount->sibur;
	destination->mendiane += amount->mendiane;
	destination->phiras += amount->phiras;
	destination->thystame += amount->thystame;
	destination->food += amount->food;
}

/// Empty an inventory into another
void inventory_move(inventory_t *destination, inventory_t *source)
{
	inventory_give(destination, source);
	inventory_take(source, source);
}
