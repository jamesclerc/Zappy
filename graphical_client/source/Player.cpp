/*
** EPITECH PROJECT, 2018
** Player.cpp
** File description:
** player
*/

#include "Player.hpp"

gpc::Player::Player(int x, int y, gpc::Entities entity, int playerId, gpc::Direction dir, gpc::Tiles *tile, int lvl, std::string team, std::vector<std::vector<sf::Sprite>> &sprites, sf::RenderTexture &window) :
	IEntity(x,y, window),
	_id(playerId),
	_direction(dir),
	_currentTile(tile),
	_lvl(lvl),
	_team(team),
	_sprites(sprites)
{
	_idEntity = entity;
}

gpc::Player::~Player()
{
}

void gpc::Player::draw()
{
	int i;

	switch(_direction)
	{
		case gpc::Direction::SOUTH:
		i = 0;
		break;
		case gpc::Direction::WEST:
		i = 1;
		break;
		case gpc::Direction::EAST:
		i = 2;
		break;
		case gpc::Direction::NORTH:
		i = 3;
		break;
		default:
		i = 0;
	}
	_sprites[_lvl - 1][i].setPosition(_x * 64., _y * 64.);
	_window.draw(_sprites[_lvl - 1][i]);
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
	_x += (_x < 0) ? xmax : 0;
	_y += (_y < 0) ? ymax : 0;
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
	_inventory.push_back(_currentTile->pickRessource(entitie));
}

void gpc::Player::dropInventory(gpc::Entities entitie)
{
	std::cout << std::to_string(_x) << "," << std::to_string(_y) << " ==? " << std::to_string(_currentTile->getX()) << "," << std::to_string(_currentTile->getY());
	int a = 0;
	gpc::IEntity *result = nullptr;
	std::cout << "Size = " << std::to_string(_inventory.size()) << std::endl;
	for(auto it=_inventory.begin(); it!=_inventory.end(); ++it)
	{
		std::cout << "IDDDDD = " << std::to_string(_inventory[a]->getEntities()) << std::endl;
		if (_inventory[a]->is(entitie))
		{
			std::cout << "J'ai trouvé" << std::endl;
			result = _inventory[a];
			_inventory.erase(it);
			break;
		}
		a++;
	}
	if (result == nullptr) {
		std::cout << "pdr Nullptr" << std::endl;
		return;
	}
	std::cout << "J'ajoute" << std::endl;
	result->setX(_x);
	result->setY(_y);
	_currentTile->addRessource(result);
	std::cout << "fin" << std::endl;
}

void gpc::Player::deleteInInventoryByEntities(gpc::Entities entitie)
{
	int a = 0;
	for(auto it=_inventory.begin(); it!=_inventory.end(); ++it)
	{
		if (_inventory[a]->is(entitie))
		{
			_inventory.erase(it);
			break;
		}
		a++;
	}
}