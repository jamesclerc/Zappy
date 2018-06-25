/*
** EPITECH PROJECT, 2018
** GraphicClient.cpp
** File description:
** GraphicClient
*/

#include "GraphicClient.hpp"
#include "Communication.hpp"

gpc::GraphicClient::GraphicClient() : _com(*this)
{
	initRenderWindow();
	_menu = new Menu(_window);
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
		player[3], team, pokemon_s, _vector, window_f);
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
	std::cout << "Player X:" << std::to_string(p->getX()) << " Y:" << std::to_string(p->getY()) << "Broadcast : " << msg << std::endl;
}

void gpc::GraphicClient::initConnection()
{
	_com.setIp(_menu->getIp());
	_com.setPort(_menu->getPort());
	int x = _com.firstConnection();
	std::cout << x << std::endl;
}

void gpc::GraphicClient::run()
{
	runMenu();
	initConnection();
	initRenderTexture();
	initFront();
	_window.clear();
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
	std::cout << "MAIN LOOP" << std::endl;
	sf::Event event;
	while(1)
	{
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				_window.close();
		}
		_window.clear();
		_com.mainLoop();
		_map->draw();
		_window.draw(front_s);
		_window.display();		
		//drawPlayer(); Je sais pas si on va passer par ça
	}
}

gpc::GraphicClient::~GraphicClient()
{
}

std::vector<sf::IntRect> gpc::GraphicClient::initCanarticho()
{
	std::vector<sf::IntRect> Canarticho;
	sf::IntRect D (0, 0, 384 / 12, 256 / 8);
	sf::IntRect L (0, 256 / 8, 384 / 12, 256 / 8);
	sf::IntRect R (0, 256 / 8 * 2, 384 / 12, 256 / 8);
	sf::IntRect U (0, 256 / 8 * 3, 384 / 12, 256 / 8);
	Canarticho.push_back(D);
	Canarticho.push_back(L);	
	Canarticho.push_back(R);
	Canarticho.push_back(U);
	return (Canarticho);
}

std::vector<sf::IntRect> gpc::GraphicClient::initTaurus()
{
	std::vector<sf::IntRect> Taurus;
	sf::IntRect D (384 * 4 / 12, 0, 384 / 12, 256 / 8);
	sf::IntRect L (384 * 4 / 12, 256 / 8, 384 / 12, 256 / 8);
	sf::IntRect R (384 * 4 / 12, 256 *  2 / 8 * 2, 384 / 12, 256 / 8);
	sf::IntRect U (384 * 4 / 12, 256 / 8 * 3, 384 / 12, 256 / 8);
	Taurus.push_back(D);
	Taurus.push_back(L);	
	Taurus.push_back(R);
	Taurus.push_back(U);
	return (Taurus);
}

std::vector<sf::IntRect> gpc::GraphicClient::initScarabrut()
{
	std::vector<sf::IntRect> Scarabrut;
	sf::IntRect D (384 * 7 / 12, 0, 384 / 12, 256 / 8);
	sf::IntRect L (384 * 7 / 12, 256 / 8, 384 / 12, 256 / 8);
	sf::IntRect R (384 * 7 / 12, 256 / 8 * 2, 384 / 12, 256 / 8);
	sf::IntRect U (384 * 7 / 12, 256 / 8 * 3, 384 / 12, 256 / 8);
	Scarabrut.push_back(D);
	Scarabrut.push_back(L);	
	Scarabrut.push_back(R);
	Scarabrut.push_back(U);
	return (Scarabrut);
}

std::vector<sf::IntRect> gpc::GraphicClient::initSecateur()
{
	std::vector<sf::IntRect> Secateur;
	sf::IntRect D (384 * 10 / 12, 0, 384 / 12, 256 / 8);
	sf::IntRect L (384 * 10 / 12, 256 / 8, 384 / 12, 256 / 8);
	sf::IntRect R (384 * 10 / 12, 256 / 8 * 2, 384 / 12, 256 / 8);
	sf::IntRect U (384 * 10 / 12, 256 / 8 * 3, 384 / 12, 256 / 8);
	Secateur.push_back(D);
	Secateur.push_back(L);	
	Secateur.push_back(R);
	Secateur.push_back(U);
	return (Secateur);
}

std::vector<sf::IntRect> gpc::GraphicClient::initEletrick()
{
	std::vector<sf::IntRect> Electrick;
	sf::IntRect D (384 * 10 / 12, 256 * 4 / 8, 384 / 12, 256 / 8);
	sf::IntRect L (384 * 10 / 12, 256 * 5 / 8, 384 / 12, 256 / 8);
	sf::IntRect R (384 * 10 / 12, 256 * 6 / 8 * 2, 384 / 12, 256 / 8);
	sf::IntRect U (384 * 10 / 12, 256 * 7 / 8 * 3, 384 / 12, 256 / 8);
	Electrick.push_back(D);
	Electrick.push_back(L);	
	Electrick.push_back(R);
	Electrick.push_back(U);
	return (Electrick);
}

std::vector<sf::IntRect> gpc::GraphicClient::initLangue()
{
	std::vector<sf::IntRect> Langue;
	sf::IntRect D (384 * 7 / 12, 256 * 4 / 8, 384 / 12, 256 / 8);
	sf::IntRect L (384 * 7 / 12, 256 * 5 / 8, 384 / 12, 256 / 8);
	sf::IntRect R (384 * 7 / 12, 256 * 6 / 8, 384 / 12, 256 / 8);
	sf::IntRect U (384 * 7 / 12, 256 * 7 / 8, 384 / 12, 256 / 8);
	Langue.push_back(D);
	Langue.push_back(L);	
	Langue.push_back(R);
	Langue.push_back(U);
	return (Langue);
}

std::vector<sf::IntRect> gpc::GraphicClient::initMagmar()
{
	std::vector<sf::IntRect> Magmar;
	sf::IntRect D (0, 256 * 4 / 8, 384 / 12, 256 / 8);
	sf::IntRect L (0, 256 * 5 / 8, 384 / 12, 256 / 8);
	sf::IntRect R (0, 256 * 6 / 8, 384 / 12, 256 / 8);
	sf::IntRect U (0, 256 * 7 / 8, 384 / 12, 256 / 8);
	Magmar.push_back(D);
	Magmar.push_back(L);	
	Magmar.push_back(R);
	Magmar.push_back(U);
	return (Magmar);
}

std::vector<sf::IntRect> gpc::GraphicClient::initRonflex()
{
	std::vector<sf::IntRect> Ronflex;
	sf::IntRect D (384 * 4 / 12, 256 * 4 / 8, 384 / 12, 256 / 8);
	sf::IntRect L (384 * 4 / 12, 256 * 5 / 8, 384 / 12, 256 / 8);
	sf::IntRect R (384 * 4 / 12, 256 * 6 / 8, 384 / 12, 256 / 8);
	sf::IntRect U (384 * 4 / 12, 256 * 7 / 8, 384 / 12, 256 / 8);
	Ronflex.push_back(D);
	Ronflex.push_back(L);	
	Ronflex.push_back(R);
	Ronflex.push_back(U);
	return (Ronflex);
}

void gpc::GraphicClient::init_pokemon(std::string path)
{
	pokemon.loadFromFile(path);
	pokemon_s.setTexture(pokemon);
	_vector.push_back(initCanarticho());
	_vector.push_back(initTaurus());
	_vector.push_back(initScarabrut());
	_vector.push_back(initSecateur());
	_vector.push_back(initEletrick());
	_vector.push_back(initLangue());
	_vector.push_back(initMagmar());
	_vector.push_back(initRonflex());
}

void gpc::GraphicClient::initRenderWindow()
{
	_window.create(sf::VideoMode(1920, 1020, 32), "Menu", sf::Style::Default);
}

void gpc::GraphicClient::initRenderTexture()
{
	window_f.create(_window_f.getSize().x, _window.getSize().y);
	printf("%f  %f", _window.getSize().x, _window.getSize().y);
}

void gpc::GraphicClient::initFront()
{
	front.loadFromFile("./graphical_client/sprite/fond_game.png");
	front_s.setTexture(front);
	front_s.setScale(1920.f / front_s.getTexture()->getSize().x, 1020.f / front_s.getTexture()->getSize().y);
}