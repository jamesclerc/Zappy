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

void gpc::Incantation::update()
{
}

void gpc::Incantation::addPlayer(Player *p)
{
	_players.push_back(p);
}

void gpc::Incantation::finish(bool incantationResult)
{
	int i = 0;
	if (incantationResult == true)
	{
		for(std::vector<gpc::Player *>::iterator it=_players.begin(); it!=_players.end(); ++it)
		{
			_players[i]->levelUp();
		}
		i++;
	}
	else
	{
		delete(this);
	}
}