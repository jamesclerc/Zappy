/*
** EPITECH PROJECT, 2018
** Tiles.cpp
** File description:
** Tiles cpp
*/

#include "Tiles.hpp"

gpc::Tiles::Tiles(int x, int y) : _x(x), _y(y)
{

}

gpc::Tiles::~Tiles()
{

}

Tiles gpc::Tiles::getTilesinDirection(gpc::Direction dir)
{
	return *this;
}

void gpc::Tiles::addRessource(IEntity *entity)
{
	_entities.push_back(entity);
}

IEntity *gpc::Tiles::pickRessource(Entities ent)
{
	int i = 0;
	IEntity *result = nullptr;
	for(vector<IEntity *>::iterator it=_entities.begin(); it!=_entities.end(); ++it)
	{
		if (*it.is(ent))
		{
			result_= _entities[i];
			_entities.erase(it);
			break;
		}
		i++;
	}
	return *result;
}