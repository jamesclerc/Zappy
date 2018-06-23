/*
** EPITECH PROJECT, 2018
** Player.cpp
** File description:
** player
*/

#include "Player.hpp"

gpc::Player::Player(int x, int y, gpc::Entities entity, int playerId, gpc::Direction dir, gpc::Tiles &tile, int lvl) : 
	IEntity(x,y),
	_id(playerId),
	_direction(dir),
	_currentTile(tile),
	_lvl(lvl)
{
	_idEntity = entity;
}

gpc::Player::~Player()
{
}

void gpc::Player::draw()
{

}

void gpc::Player::update()
{
}

void gpc::Player::levelUp()
{
	_lvl++;
}

void gpc::Player::setLevel(int lvl)
{
	_lvl = lvl;
}

void gpc::Player::moveForward()
{
	//a coder
}

void gpc::Player::addInInventory(gpc::IEntity *entity)
{
	_inventory.push_back(entity);
}

void gpc::Player::deleteInInventory(gpc::IEntity *entity)
{
	int a = 0;
	for(std::vector<IEntity *>::iterator it=_inventory.begin(); it!=_inventory.end(); ++it)
	{
		if (_inventory[a] == entity)
		{
			_inventory.erase(it);
			break;
		}
		a++;
	}
}

void gpc::Player::pickToInventory(gpc::Entities entitie)
{
	_inventory.push_back(new gpc::Ressource(_x, _y, entitie));
}

void gpc::Player::dropInventory(gpc::Entities entitie)
{
	int a = 0;
	gpc::IEntity *result = nullptr;
	for(std::vector<gpc::IEntity *>::iterator it=_inventory.begin(); it!=_inventory.end(); ++it)
	{
		if (_inventory[a]->is(entitie))
		{
			result = _inventory[a];
			_inventory.erase(it);
			break;
		}
		a++;
	}
	_currentTile.addRessource(result);
}

void gpc::Player::deleteInInventoryByEntities(gpc::Entities entitie)
{
	int a = 0;
	for(std::vector<gpc::IEntity *>::iterator it=_inventory.begin(); it!=_inventory.end(); ++it)
	{
		if (_inventory[a]->is(entitie))
		{
			_inventory.erase(it);
			break;
		}
		a++;
	}
}