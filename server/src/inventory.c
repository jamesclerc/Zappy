/*
** EPITECH PROJECT, 2018
** inventory.c
** File description:
** inventory related functions
*/

#include "inventory.h"

/// Checks wether an inventory contains everyting another has
//  `inventory_t a`: pointer to the checked inventory
//  `inventory_t b`: pointer to a reference inventory
//  `int retrun`: true if a has everything b has
bool inventory_has(inventory_t *a, inventory_t *b)
{
	if (a->linemate < b->linemate || a->deraumere < b->deraumere
		|| a->sibur < b->sibur || a->mendiane < b->mendiane
		|| a->phiras < b->phiras || a->thystame < b->thystame)
		return (false);
	return (true);
}
