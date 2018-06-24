/*
** EPITECH PROJECT, 2018
** Incantation.cpp
** File description:
** Incantation
*/

#include "Incantation.hpp"

gpc::Incantation::Incantation(int x, int y, Entities entity) : IEntity(x,y)
{
	_idEntity = entity;
}

gpc::Incantation::~Incantation()
{
}

void gpc::Incantation::draw()
{
}

gpc::Player *gpc::Incantation::getIncantationPlayer()
{
	return _players[0];
}

void gpc::Incantation::update()
{
}

void gpc::Incantation::addPlayer(Player *p)
{
	_players.push_back(p);
	_x = p->getX();
	_y = p->getY();
}

void gpc::Incantation::finish(bool incantationResult)
{
	int i = 0;
	if (incantationResult == true)
	{
		for(auto it=_players.begin(); it!=_players.end(); ++it)
		{
			_players[i]->levelUp();
		}
		i++;
	}
}