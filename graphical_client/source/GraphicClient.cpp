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
			for (int y = 0; y < ressources[i];y++)
				tile->addRessource(new Ressource(x, y, entitie[i]));
		i++;
	}
}

void gpc::GraphicClient::createEgg(int x, int y, int id)
{
	_eggs.push_back(new Egg(x, y, Entities::EGG, id));
}

void gpc::GraphicClient::ressourcePop(int x, int y, int i)
{
	gpc::Tiles *tile = _map->getTiles(x,y);
	tile->addRessource(new Ressource(x, y, entitie[i]));
}

void gpc::GraphicClient::playerGet(int n, int i)
{
	gpc::Player *p = getPlayer(n);
	p->pickToInventory(entitie[i]);
}

void gpc::GraphicClient::playerDrop(int n, int i)
{
	gpc::Player *p = getPlayer(n);
	p->dropInventory(entitie[i]);
}

void gpc::GraphicClient::playerEat(int n)
{
	Player *p = getPlayer(n);
	p->deleteInInventoryByEntities(gpc::Entities::FOOD);
}

void gpc::GraphicClient::playerMoveForward(int n)
{
	Player *p = getPlayer(n);
	p->moveForward(_map->getX(), _map->getY());
	p->setCurrentTile(_map->getTiles(p->getX(), p->getY()));
}

gpc::Incantation *gpc::GraphicClient::getIncantation(int n)
{
	Player *p = getPlayer(n);
	int i = 0;
	for(auto it=_incantations.begin(); it!=_incantations.end(); it++)
	{
		if (_incantations[i]->getIncantationPlayer() == p)
			return _incantations[i];
		i++;
	}
	return nullptr;
}

void gpc::GraphicClient::playerDie(int n)
{
	int i = 0;
	for(auto it=_players.begin(); it!=_players.end(); it++)
	{
		if (_players[i]->getId() == n) {
			_players.erase(it);
			return;
		}
		i++;
	}
}

void gpc::GraphicClient::finishAll()
{
	std::cout << "Fin de la partie" << std::endl;
}

void gpc::GraphicClient::incantationFinish(int n, std::string result)
{
	gpc::Incantation *inc = getIncantation(n);
	if (inc == nullptr)
		return;
	if (result.compare("ok"))
		inc->finish(true);
	else
		inc->finish(false);
	int i = 0;
	for(auto it=_incantations.begin(); it!=_incantations.end(); it++)
	{
		if (_incantations[i] == inc) {
			_incantations.erase(it);
			return;
		}
		i++;
	}
}

void gpc::GraphicClient::eggDie(int n)
{
	int i = 0;
	for(auto it=_eggs.begin(); it!=_eggs.end(); it++)
	{
		if (_eggs[i]->getId() == n) {
			_eggs.erase(it);
			return;
		}
		i++;
	}
}

void gpc::GraphicClient::hatchingEgg(int id)
{
	int i = 0;
	for(std::vector<Egg *>::iterator it=_eggs.begin(); it!=_eggs.end(); ++it)
	{
		if(_eggs[i]->getId() == id)
		{
			_eggs[i]->hatching();
			return;
		}
		i++;
	}
}

gpc::Player *gpc::GraphicClient::getPlayer(int id)
{
	int i = 0;
	for(auto it=_players.begin(); it!=_players.end(); it++)
	{
		if (_players[i]->getId() == id)
			return _players[i];
		i++;
	}
	return nullptr;
}

void gpc::GraphicClient::addIncantation(std::vector<int> incantation)
{
	gpc::Incantation *inc = new Incantation(0, 0, Entities::INCANTATION);
	int i = 0;
	for(std::vector<int>::iterator it=incantation.begin(); it!=incantation.end(); it++)
	{
		inc->addPlayer(getPlayer(incantation[i]));
		i++;
	}
}

void gpc::GraphicClient::playerTurn(int n, std::string dir)
{
	Player *p = getPlayer(n);
	gpc::Direction dire;
	if (dir.compare("N"))
		dire = gpc::NORTH;
	if (dir.compare("W"))
		dire = gpc::WEST;
	if (dir.compare("E"))
		dire = gpc::EAST;
	if (dir.compare("S"))
		dire = gpc::SOUTH;
	p->setDir(dire);
}

void gpc::GraphicClient::addPlayer(std::string dir, std::string team, std::vector<int> player)
{
	Player *p;
	gpc::Direction dire;
	if (dir.compare("N"))
		dire = gpc::NORTH;
	if (dir.compare("W"))
		dire = gpc::WEST;
	if (dir.compare("E"))
		dire = gpc::EAST;
	if (dir.compare("S"))
		dire = gpc::SOUTH;
	p = new Player(player[1], player[2],
		Entities::PLAYER, player[0],
		dire, _map->getTiles(player[1], player[2]),
		player[3], team);
	int i = 4;
	for(std::vector<int>::iterator it=player.begin(); it!=player.end(); ++it)
	{
		for (int y = 0; y < player[i];y++)
			p->addInInventory(new Ressource(player[1], player[2], entitie[i]));
		i++;
	}
	_players.push_back(p);
}

void gpc::GraphicClient::playerBroadcast(int n, std::string msg)
{
	Player *p = getPlayer(n);
	std::cout << "Broadcast : " << msg << std::endl;
}

void gpc::GraphicClient::initConnection()
{
	_com.setIp(_menu->getIp());
	_com.setPort(_menu->getPort());
	_com.firstConnection();
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
