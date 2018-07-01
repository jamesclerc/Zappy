/*
** EPITECH PROJECT, 2018
** GraphicClient.cpp
** File description:
** GraphicClient
*/

#include "GraphicClient.hpp"
#include "Communication.hpp"

gpc::GraphicClient::GraphicClient() : _com(*this), _isDrawable(false)
{
	initSound();
	initRenderWindow();
	initRenderTexture();
	initFloor();
	initFront();
	initMaterial();
	initPlayerSprites();
	initEgg();
	initHud();
	_view_is_init = false;
	_scaling = 1.f;
	_menu = new Menu(_window);
}

void gpc::GraphicClient::initFloor()
{
	floor.loadFromFile("./graphical_client/sprite/sprite_floor.png");
	floor_s.setTexture(floor);
}

void gpc::GraphicClient::constructMap(int x, int y)
{
	_map = new Map(x, y, floor_s, window_f);
	_isDrawable = true;
}

void gpc::GraphicClient::completeTiles(int x, int y, std::vector<int> ressources)
{
	Tiles *tile = _map->getTiles(x, y);

	std::cout << "x = " << std::to_string(x) << std::endl << "y = " << std::to_string(y) << std::endl;
	int i = 0;
	for(std::vector<int>::iterator it=ressources.begin(); it!=ressources.end(); ++it)
	{
			for (int tmp = 0; tmp < ressources[i]; tmp++)
				tile->addRessource(new Ressource(x, y, entitie[i], window_f, _material[i]));
		i++;
	}
}

void gpc::GraphicClient::createEgg(int x, int y, int id)
{
	_eggs.push_back(new Egg(x, y, Entities::EGG, id, window_f, _egg));
}

void gpc::GraphicClient::ressourcePop(int x, int y, int i)
{
	gpc::Tiles *tile = _map->getTiles(x,y);
	tile->addRessource(new Ressource(x, y, entitie[i], window_f, _material[i]));
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
	if (p == nullptr) {
		std::cout << "PLAYER NULL IN EAT" << std::endl;
		return;
	}
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
	int i = 0;
	std::cout << "Incantation size = " << std::to_string(_incantations.size()) << std::endl;
	for(auto it=_incantations.begin(); it!=_incantations.end(); it++)
	{
		std::cout << "get Incantation : " << std::to_string(i) << std::endl;
		if (_incantations[i]->getIncantationPlayer()->getId() == n)
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
	if (inc == nullptr) {
		std::cout << "inc nullptr" << std::endl;
		return;
	}
	std::cout << "RESULT = " << result << std::endl;
	if (result.compare("ok") == 0)
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
	std::cout << "GET PLAYER : " << std::to_string(id) << std::endl;
	for(auto it=_players.begin(); it!=_players.end(); it++)
	{
		std::cout << "Player ID = " << std::to_string(_players[i]->getId()) << std::endl;
		if (_players[i]->getId() == id)
			return _players[i];
		i++;
	}
	return nullptr;
}

void gpc::GraphicClient::addIncantation(std::vector<int> incantation)
{
	gpc::Incantation *inc = new Incantation(0, 0, Entities::INCANTATION, window_f);
	int i = 0;
	for(std::vector<int>::iterator it=incantation.begin(); it!=incantation.end(); it++)
	{
		inc->addPlayer(getPlayer(incantation[i]));
		i++;
	}
	inc->setIncantationOnTile();
	_incantations.push_back(inc);
}

void gpc::GraphicClient::playerTurn(int n, int dir)
{
	Player *p = getPlayer(n);
	gpc::Direction dire;
	switch(dir) {
		case 1:
		dire = gpc::NORTH;
		break;
		case 2:
		dire = gpc::EAST;
		break;
		case 3:
		dire = gpc::SOUTH;
		break;
		case 4:
		dire = gpc::WEST;
		break;
	}
	p->setDir(dire);
}

void gpc::GraphicClient::addPlayer(int dir, std::string team, std::vector<int> player)
{
	Player *p;
	gpc::Direction dire;
	switch(dir) {
		case 1:
		dire = gpc::NORTH;
		break;
		case 2:
		dire = gpc::EAST;
		break;
		case 3:
		dire = gpc::SOUTH;
		break;
		case 4:
		dire = gpc::WEST;
		break;
	}
	p = new Player(player[1], player[2],
		Entities::PLAYER, player[0],
		dire, _map->getTiles(player[1], player[2]),
		player[3], team, player_sprites, window_f);
	int i = 0;
	int tmp = 0;
	for(std::vector<int>::iterator it=player.begin(); it!=player.end(); ++it)
	{
		if (i < 4)
		{
			i++;
			continue;
		}
		std::cout << "avant i = " << std::to_string(i) << std::endl;
		for (int y = 0; y < player[i];y++)
			p->addInInventory(new Ressource(player[1], player[2], entitie[tmp], window_f, _material[tmp]));
		std::cout << "après" << std::endl;
		i++;
		tmp++;
	}
	_players.push_back(p);
}

void gpc::GraphicClient::playerBroadcast(int n, std::string msg)
{
	Player *p = getPlayer(n);
	std::cout << "Player X:" << std::to_string(p->getX()) << " Y:" << std::to_string(p->getY()) << "Broadcast : " << msg << std::endl;
}

int gpc::GraphicClient::initConnection()
{
	_com.setIp(_menu->getIp());
	_com.setPort(_menu->getPort());
	int x = _com.firstConnection();
	std::cout << x << std::endl;
	return x;
}

void gpc::GraphicClient::run()
{
	runMenu();
	if (initConnection() != 0)
		run();
	else {
		_window.clear();
		mainLoop();
	}
}

void gpc::GraphicClient::setTimer(int timer)
{
	_com.newSpeed(timer);
	_timer = timer;
}

void gpc::GraphicClient::runMenu()
{
	_menu->setState(Menu::state::FIRST);
	bool test = false;
	while (test == false)
	{
		test = _menu->draw();
	}
}

void gpc::GraphicClient::initView()
{
	int x = _map->getX();
	int y = _map->getY();
	float ratio = (float)y / (float)x;

	if (_view_is_init) {
		return;
	}
	view.setCenter(_map->getX() * 32, _map->getY() * 32);
	if (ratio > 437.f / 656.f)
		view.setSize(sf::Vector2f(y * 64 * (656.f / 437.f), y * 64));
	else
		view.setSize(sf::Vector2f(x * 64, x * 64 * (437.f / 656.f)));
	view.setViewport(sf::FloatRect((20.f / 1024.f), (71.f / 519.f), (656.f / 1024.f), (437.f / 519.f)));
	window_f.setView(view);
	_view_is_init = true;
}

void gpc::GraphicClient::handleZoomEvent(sf::Event &event)
{
	if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta == -1)
		_scaling = (_scaling < 0.9f) ? _scaling + 0.1f : 1.f;
	else if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta == 1)
		_scaling = (_scaling > 0.2f) ? _scaling - 0.1f : 0.2f;
}

void gpc::GraphicClient::handleMoveEvent(sf::Event &event)
{
	if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta == -1)
		view.move(0, 10);
	else if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta == 1)
		view.move(0, -10);
	else if(event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel && event.mouseWheelScroll.delta == -1)
		view.move(10, 0);
	else if(event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel && event.mouseWheelScroll.delta == 1)
		view.move(-10, 0);
}

void gpc::GraphicClient::handleEvent(sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i pixelPos = sf::Mouse::getPosition(_window);
        	sf::Vector2f worldPos = window_f.mapPixelToCoords(pixelPos);
        	changeTilefocus(worldPos.x / 64.f, worldPos.y / 64.f);
	}
	if (event.type == sf::Event::MouseWheelScrolled && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
		handleMoveEvent(event);
		window_f.setView(view);
	} else if (event.type == sf::Event::MouseWheelScrolled) {
		handleZoomEvent(event);
		window_f.setView(view);
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Right) {
			_timer += 1;
		} else if (event.key.code == sf::Keyboard::Left) {
			_timer -= 1;
			if (_timer < 2)
				_timer = 2;
		}
	}
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
		{
			setTimer(_timer);
		}
	}
}

void gpc::GraphicClient::mainLoop()
{
	sf::Texture texture;
	sf::Sprite sprite;
	while(_window.isOpen())
	{
		sf::Event event;
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_window.close();				
			}
			handleEvent(event);
		}
		_window.clear();
		_com.mainLoop();
		if (_isDrawable) {
			initView();
			sf::View tmp(view);
			tmp.zoom(_scaling);
			window_f.setView(tmp);
			_map->draw();
			drawEggs();
			drawPlayers();
			texture = window_f.getTexture();
			sprite.setTexture(texture);
			_window.draw(sprite);
			_window.draw(front_s);
			drawHud();
			_window.display();
		}
	}
}

gpc::GraphicClient::~GraphicClient()
{
}

void gpc::GraphicClient::initRenderWindow()
{
	_window.create(sf::VideoMode(1920, 1020, 32), "Menu", sf::Style::Default);
}

void gpc::GraphicClient::initRenderTexture()
{
	window_f.create(_window.getSize().x, _window.getSize().y);
}

void gpc::GraphicClient::initFront()
{
	front.loadFromFile("./graphical_client/sprite/fond_game.png");
	front_s.setTexture(front);
	front_s.setScale(1920.f / front_s.getTexture()->getSize().x, 1020.f / front_s.getTexture()->getSize().y);
}

void gpc::GraphicClient::initThystame(sf::Texture &texture)
{
	sf::IntRect ressource;
	sf::Sprite *sprite = new sf::Sprite;

	ressource.left = 670;
	ressource.top = 10;
	ressource.width = 356 - 270;
	ressource.height = 90;
	sprite->setTexture(texture);
	sprite->setTextureRect(ressource);
	_material.push_back(*sprite);
}

void gpc::GraphicClient::initDeraumere(sf::Texture &texture)
{
	sf::IntRect deraumere;
	sf::Sprite *sprite = new sf::Sprite;

	deraumere.left = 405;
	deraumere.top = 10;
	deraumere.width = 356 - 270;
	deraumere.height = 90;
	sprite->setTexture(texture);
	sprite->setTextureRect(deraumere);
	_material.push_back(*sprite);
}

void gpc::GraphicClient::initFood(sf::Texture &texture)
{
	sf::IntRect food;
	sf::Sprite *sprite = new sf::Sprite;

	food.left = 0;
	food.top = 0;
	food.width = 521 - 521 * 7/ 8;
	food.height = 520 - 520 * 6 / 7;
	sprite->setTexture(texture);
	sprite->setTextureRect(food);
	_material.push_back(*sprite);
}

void gpc::GraphicClient::initLinemate(sf::Texture &texture)
{
	sf::IntRect linemate;
	sf::Sprite *sprite = new sf::Sprite;

	linemate.left = 270;
	linemate.top = 10;
	linemate.width = 356 - 270;
	linemate.height = 90;
	sprite->setTexture(texture);
	sprite->setTextureRect(linemate);
	_material.push_back(*sprite);
}

void gpc::GraphicClient::initSibur(sf::Texture &texture)
{
	sf::IntRect sibur;
	sf::Sprite *sprite = new sf::Sprite;

	sibur.left = 536;
	sibur.top = 10;
	sibur.width = 356 - 270;
	sibur.height = 90;
	sprite->setTexture(texture);
	sprite->setTextureRect(sibur);
	_material.push_back(*sprite);
}
void gpc::GraphicClient::initMendiane(sf::Texture &texture)
{
	sf::IntRect mendiane;
	sf::Sprite *sprite = new sf::Sprite;

	mendiane.left = 405;
	mendiane.top = 110;
	mendiane.width = 356 - 270;
	mendiane.height = 100;
	sprite->setTexture(texture);
	sprite->setTextureRect(mendiane);
	_material.push_back(*sprite);
}
void gpc::GraphicClient::initPhiras(sf::Texture &texture)
{
	sf::IntRect phiras;
	sf::Sprite *sprite = new sf::Sprite;

	phiras.left = 800;
	phiras.top = 10;
	phiras.width = 356 - 270;
	phiras.height = 90;
	sprite->setTexture(texture);
	sprite->setTextureRect(phiras);
	_material.push_back(*sprite);
}

void gpc::GraphicClient::initMaterial()
{
	material_t.loadFromFile("./graphical_client/sprite/material.png");
	food_t.loadFromFile("./graphical_client/sprite/bouffe.png");
	initFood(food_t);
	initLinemate(material_t);
	initDeraumere(material_t);
	initSibur(material_t);
	initMendiane(material_t);
	initPhiras(material_t);
	initThystame(material_t);
}

void gpc::GraphicClient::initEgg()
{
	sf::Sprite *sprite = new sf::Sprite;
	sf::Sprite *sprite_hatch = new sf::Sprite;

	egg_t.loadFromFile("./graphical_client/sprite/eggs.png");
	sprite->setTexture(egg_t);
	_egg.push_back(*sprite);
	eggHatch_t.loadFromFile("./graphical_client/sprite/hatching_egg.png");
	sprite_hatch->setTexture(eggHatch_t);
	_egg.push_back(*sprite_hatch);
}

void gpc::GraphicClient::initLevelSprites(sf::IntRect rect)
{
	sf::Sprite *tmp;
	std::vector<sf::Sprite> *level_sprites = new std::vector<sf::Sprite>;
	int i = 0;

	while (i < 4) {
		tmp = new sf::Sprite;
		tmp->setTexture(player_texture);
		tmp->setTextureRect(rect);
		rect.top += 256 / 8;
		level_sprites->push_back(*tmp);
		i++;
	}
	player_sprites.push_back(*level_sprites);
}

void gpc::GraphicClient::initPlayerSprites()
{
	sf::IntRect rect (384 / 12, 0, 384 / 12, 256 / 8);
	int i = 0;

	player_texture.loadFromFile("./graphical_client/sprite/sprite.png");
	while (i < 8) {
		if (i % 4 == 0)
			rect.left = 0;
		else
			rect.left += 384 / 4;
		if (i > 0 && i % 4 == 0)
			rect.top += 384 / 2;
		initLevelSprites(rect);
		i++;
	}

}

void gpc::GraphicClient::drawPlayers()
{
	for (size_t i = 0; i < _players.size(); i++) {
		_players[i]->draw();
	}
}

void gpc::GraphicClient::drawEggs()
{
	for (size_t i = 0; i < _eggs.size(); i++) {
		_eggs[i]->draw();
	}
}

void gpc::GraphicClient::changeTilefocus(float x, float y)
{
	if (x >= (float)_map->getX() || y >= (float)_map->getY())
		return;
	if (x < 0 || y < 0)
		return;
	_tileFocus = _map->getTiles(static_cast<int>(x), static_cast<int>(y));
}

void gpc::GraphicClient::initHud()
{
	_font.loadFromFile("./graphical_client/font/Pokemon Classic.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(30);
	_text.setFillColor(sf::Color::Black);
	_text.setStyle(sf::Text::Bold);
}

void gpc::GraphicClient::initSound()
{
	if (!_buffer.loadFromFile("./graphical_client/sounds/pokemonMenu.wav")) {
		std::cout << "Error loading wav" << std::endl;
	}
	_sound.setBuffer(_buffer);
	_sound.play();
}

void gpc::GraphicClient::drawHud()
{
	_text.setPosition(800, 20);
	_text.setString(std::string("Speed : " + std::to_string(_timer)));
	_window.draw(_text);
	if (_tileFocus == nullptr)
		return;
	float initialPosX = 1300 - 86;
	float initialPosY = 400;
	_text.setPosition(initialPosX + 86, initialPosY - 40);
	_text.setString(std::string("X = " + std::to_string(_tileFocus->getX()) + " Y = " + std::to_string(_tileFocus->getY())));
	_window.draw(_text);
	std::vector<int> nbRessources = _tileFocus->getNbRessources();
	for (int i = 0; i < 7; i++) {
		initialPosX += 86;
		_material[i].setPosition(initialPosX,initialPosY);
		if (i == 0)
			_material[i].setScale(1.8,1.8);
		else
			_material[i].setScale(1.,1.);
		_text.setPosition(initialPosX + 30, initialPosY + 120);
		_text.setString(std::to_string(nbRessources[i]));
		_window.draw(_material[i]);
		_window.draw(_text);
	}
	_window.draw(_text);
}