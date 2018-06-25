/*
** EPITECH PROJECT, 2018
** Map.cpp
** File description:
** map
*/

#include "Map.hpp"
#include <iostream>

gpc::Map::Map(int x, int y) : _x(x), _y(y)
{
	for (int i = 0; i < x; i++)
		_map.push_back(getVectorTiles(i, y));
}

gpc::Map::~Map()
{
}

int gpc::Map::getX()
{
	return _x;
}

int gpc::Map::getY()
{
	return _y;
}

std::vector<gpc::Tiles *> gpc::Map::getVectorTiles(int x, int y)
{
	std::vector<gpc::Tiles *> tiles;

	for(int i = 0; i < y; i++)
		tiles.push_back(new Tiles(x, i));
	return tiles;
}

gpc::Tiles * gpc::Map::getTiles(int x, int y)
{
	return _map[x][y];
}

void gpc::Map::draw()
{
	// std::cout << "draw of the map" << std::endl;
}