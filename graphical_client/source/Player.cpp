/*
** EPITECH PROJECT, 2018
** Player.cpp
** File description:
** player
*/

#include "Player.hpp"

gpc::Player::Player(int x, int y, gpc::Entities entity, int playerId, gpc::Direction dir, gpc::Tiles *tile, int lvl, std::string team) :
	IEntity(x,y),
	_id(playerId),
	_direction(dir),
	_currentTile(tile),
	_lvl(lvl),
	_team(team)
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

int gpc::Player::getId()
{
	return _id;
}

void gpc::Player::setCurrentTile(gpc::Tiles *tile)
{
	_currentTile = tile;
}

void gpc::Player::setDir(gpc::Direction dir)
{
	_direction = dir;
}

void gpc::Player::moveForward(int xmax, int ymax)
{
	switch(_direction)
	{
		case Direction::NORTH:
		_y--;
		break;
		case Direction::SOUTH:
		_y++;
		break;
		case Direction::WEST:
		_x--;
		break;
		case Direction::EAST:
		_x++;
		break;
	}
	_y %= ymax;
	_x %= xmax;
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
	_currentTile->addRessource(result);
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