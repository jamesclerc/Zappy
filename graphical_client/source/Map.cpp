/*
** EPITECH PROJECT, 2018
** Map.cpp
** File description:
** map
*/

#include "Map.hpp"

gpc::Map::Map(int x, int y)
{
	for (int i = 0, i < x, i++)
		_map.push_back getVectorTiles(i, y);
}

gpc::Map::~Map()
{
}

std::vector<Tiles *> gpc::Map::getVectorTiles(int x, int y)
{
	std::vector<Tiles *> tiles;

	for(int i = 0; i < y; i++)
		tiles.push_back(new Tiles(x, i));
	return tiles;
}

Tiles * gpc::Map::getTiles(int x, int y)
{
	return _map[x][y];
}

void gpc::Map::draw()
{
}