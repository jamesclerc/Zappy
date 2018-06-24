/*
** EPITECH PROJECT, 2018
** GraphicClient.cpp
** File description:
** GraphicClient
*/

#include "GraphicClient.hpp"
#include "Communication.hpp"

gpc::GraphicClient *gpc::GraphicClient::_instance = nullptr;

gpc::GraphicClient::GraphicClient(sf::RenderWindow *window, gpc::Menu *menu) : _menu(menu), _window(window), _com(*this)
{
}

void gpc::GraphicClient::setTimer(int timer)
{
	_timer = timer;
}

void gpc::GraphicClient::constructMap(int x, int y)
{
	_map = new Map(x, y);
}

void gpc::GraphicClient::completeTiles(int x, int y, std::vector<int> ressources)
{
	Tiles *tile = _map->getTiles(x, y);
	int i = 0;
	for(std::vector<int>::iterator it=ressources.begin(); it!=ressources.end(); ++it)
	{
		switch(i)
		{
			case 0:
			for (int y = 0; y < ressources[i];y++)
				tile->addRessource(new Ressource(x, y, gpc::Entities::FOOD));
			break;
			case 1:
			for (int y = 0; y < ressources[i];y++)
				tile->addRessource(new Ressource(x, y, gpc::Entities::LINEMATE));
			break;
			case 2:
			for (int y = 0; y < ressources[i];y++)
				tile->addRessource(new Ressource(x, y, gpc::Entities::DERAUMERE));
			break;
			case 3:
			for (int y = 0; y < ressources[i];y++)
				tile->addRessource(new Ressource(x, y, gpc::Entities::SIBUR));
			break;
			case 4:
			for (int y = 0; y < ressources[i];y++)
				tile->addRessource(new Ressource(x, y, gpc::Entities::MENDIANE));
			break;
			case 5:
			for (int y = 0; y < ressources[i];y++)
				tile->addRessource(new Ressource(x, y, gpc::Entities::PHIRAS));
			break;
			case 6:
			for (int y = 0; y < ressources[i];y++)
				tile->addRessource(new Ressource(x, y, gpc::Entities::THYSTAME));
			break;
		}
		i++;
	}
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
