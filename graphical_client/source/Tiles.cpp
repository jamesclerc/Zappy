/*
** EPITECH PROJECT, 2018
** Tiles.cpp
** File description:
** Tiles cpp
*/

#include "Tiles.hpp"
#include <iostream>

gpc::Tiles::Tiles(int x, int y, sf::Sprite &floor, sf::RenderTexture &window) : _x(x), _y(y), _floor(floor), _window(window)
{

}

gpc::Tiles::~Tiles()
{

}

int gpc::Tiles::getX()
{
	return _x;
}

int gpc::Tiles::getY()
{
	return _y;
}

void gpc::Tiles::addRessource(IEntity *entity)
{
	_entities.push_back(entity);
}

gpc::IEntity *gpc::Tiles::pickRessource(gpc::Entities ent)
{
	int i = 0;
	gpc::IEntity *result = nullptr;
	for(std::vector<IEntity *>::iterator it=_entities.begin(); it!=_entities.end(); ++it)
	{
		if (_entities[i]->is(ent))
		{
			std::cout << "J'ai trouvé" << std::endl;
			result= _entities[i];
			_entities.erase(it);
			break;
		}
		i++;
	}
	return result;
}

void gpc::Tiles::drawEntities()
{
	for (int i = 0; i < _entities.size(); i++) {
		_entities[i]->draw();
	}
}

void gpc::Tiles::draw()
{
	sf::Color sol_c;

	sol_c = _floor.getColor();
	if (_y % 2 == 0 && _x % 2 == 0)
		sol_c.a = 235;
	else if (_y % 2 == 1 && _x % 2 == 1)
		sol_c.a = 235;
	else
		sol_c.a = 255;
	_floor.setColor(sol_c);
	_floor.setPosition(_x * 64., _y * 64.);
	_window.draw(_floor);
	drawEntities();
}