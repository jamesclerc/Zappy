/*
** EPITECH PROJECT, 2018
** map.h
** File description:
** Map header file
*/

#ifndef MAP_H_
# define MAP_H_

#include "inventory.h"

typedef inventory_t** map_t;

map_t create_map(int width, int height);

#endif /* !MAP_H_ */
