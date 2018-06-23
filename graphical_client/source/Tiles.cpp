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

gpc::Tiles &gpc::Tiles::getTilesInDirection(Direction dir)
{
	return *this;
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
			result= _entities[i];
			_entities.erase(it);
			break;
		}
		i++;
	}
	return result;
}