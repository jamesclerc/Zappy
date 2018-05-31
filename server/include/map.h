/*
** EPITECH PROJECT, 2018
** map.h
** File description:
** Map header file
*/

#ifndef MAP_H_
# define MAP_H_

#include "inventory.h"

typedef struct map_s {
	inventory_t **data;
	int width;
	int height;
} map_t;

map_t *create_map(int width, int height);

#endif /* !MAP_H_ */
