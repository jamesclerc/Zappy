/*
** EPITECH PROJECT, 2018
** Map.cpp
** File description:
** map
*/

#include "Map.hpp"
#include <iostream>

gpc::Map::Map(int x, int y, sf::Sprite &floor, sf::RenderTexture &window) : _x(x), _y(y), _floor(floor), _window(window)
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
		tiles.push_back(new Tiles(x, i, _floor, _window));
	return tiles;
}

gpc::Tiles * gpc::Map::getTiles(int x, int y)
{
	return _map[x][y];
}

void gpc::Map::draw()
{
	_window.clear();
	for (int i = 0; i < _x; i++)
	{
		for (int j = 0; j < _y; j++) {
			_map[i][j]->draw();
		}
	}
	_window.display();
}