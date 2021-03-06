/*
** EPITECH PROJECT, 2018
** Incantation.cpp
** File description:
** Incantation
*/

#include "Incantation.hpp"

gpc::Incantation::Incantation(int x, int y, Entities entity, sf::RenderTexture &window) : IEntity(x,y, window)
{
	_idEntity = entity;
}

gpc::Incantation::~Incantation()
{
}

void gpc::Incantation::setIncantationOnTile()
{
	_players[0]->getCurrentTile()->setIncantation(true);
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
	std::cout << "Incantation FInish" << std::endl;
	int i = 0;
	if (incantationResult == true)
	{
		std::cout << "Incantation result : true" << std::endl;
		for(auto it=_players.begin(); it!=_players.end(); ++it)
		{
			_players[i]->levelUp();
			i++;
		}
	}
	_players[0]->getCurrentTile()->setIncantation(false);
}
