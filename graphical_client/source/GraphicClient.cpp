/*
** EPITECH PROJECT, 2018
** GraphicClient.cpp
** File description:
** GraphicClient
*/

#include "GraphicClient.hpp"

gpc::GraphicClient *gpc::GraphicClient::_instance = nullptr;

gpc::GraphicClient::GraphicClient(sf::RenderWindow *window, gpc::Menu *menu) : _menu(menu), _window(window)
{
}

gpc::GraphicClient *gpc::GraphicClient::getInstance()
{
	if (!_instance) {
		sf::RenderWindow *window = new sf::RenderWindow;
		_instance = new GraphicClient(window, new gpc::Menu(*window));
	}
	return _instance;
}

void gpc::GraphicClient::initConnection()
{
	_com.setIp(_menu->getIp());
	_com.setPort(_menu->getPort());
	_com.firstConnection();
}

void gpc::GraphicClient::addPlayer(Player p)
{
	_players.push_back(p);
}

void gpc::GraphicClient::run()
{
	runMenu();
	initConnection();
	mainLoop();
}

void gpc::GraphicClient::runMenu()
{
	bool test = false;
	while (test == false)
	{
		test = _menu->draw();
	}
}

void gpc::GraphicClient::mainLoop()
{
	while(1)
	{
		_com.mainLoop();
		_map->draw();
		//drawPlayer(); Je sais pas si on va passer par ça
	}
}
gpc::GraphicClient::~GraphicClient()
{
}
