/*
** EPITECH PROJECT, 2018
** Egg.cpp
** File description:
** Egg.cpp
*/

#include "Egg.hpp"

gpc::Egg::Egg(int x, int y, Entities entity, int eggId, sf::RenderTexture &window, std::vector<sf::Sprite> &sprite) : IEntity(x,y, window), _id(eggId), _hatching(false), _sprite(sprite)
{
	_idEntity = entity;
}

gpc::Egg::~Egg()
{
}

int gpc::Egg::getId()
{
	return _id;
}

void gpc::Egg::hatching()
{
	_hatching = true;
}

void gpc::Egg::draw()
{
	if (!_hatching) {
		_sprite[0].setScale(0.3f, 0.3f);
		_sprite[0].setPosition(_x * 64 + 32, _y * 64 + 32);
		_window.draw(_sprite[0]);
	} else {
		_sprite[1].setScale(0.2f, 0.2f);
		_sprite[1].setPosition(_x * 64 + 32, _y * 64 + 32);
		_window.draw(_sprite[1]);
	}
}

void gpc::Egg::update()
{

}