//
// EPITECH PROJECT, 2018
// GraphicClient.hpp
// File description:
// GraphicClient class
//

#pragma once

#include <vector>
#include <iostream>

#include "Player.hpp"
#include "Egg.hpp"
#include "Incantation.hpp"
#include "Map.hpp"
#include "menu.hpp"
#include "Communication.hpp"

namespace gpc {
	class GraphicClient {
		public:
			GraphicClient(sf::RenderWindow *window, gpc::Menu *menu);
			~GraphicClient();
			void constructMap(int x, int y);
			void completeTiles(int x, int y, std::vector<int> ressources);
			void setTimer(int timer);
			void playerDrop(int n, int i);
			void playerGet(int n, int i);
			void createEgg(int x, int y, int id);
			void playerEat(int n);
			void playerMoveForward(int n);
			void playerBroadcast(int n, std::string msg);
			void playerTurn(int n , std::string dir);
			void incantationFinish(int n, std::string result);
			void eggDie(int n);
			gpc::Incantation *getIncantation(int n);
			void playerDie(int n);
			void finishAll();
			void hatchingEgg(int id);
			gpc::Player *getPlayer(int id);
			void ressourcePop(int x, int y, int i);
			void addIncantation(std::vector<int> incantation);
			void addPlayer(std::string dir, std::string team, std::vector<int> player);
			void run();
		private:
			int _timer;
			void runMenu();
			void initConnection();
			void mainLoop();
			sf::RenderWindow *_window;
			static GraphicClient *_instance;
			std::vector<gpc::Player *> _players;
			std::vector<gpc::Egg *> _eggs;
			std::vector<gpc::Incantation *> _incantations;
			gpc::Menu *_menu;
			Communication _com;
			gpc::Map *_map;
	};
}

static gpc::Entities entitie[7] = {
	gpc::Entities::FOOD,
	gpc::Entities::LINEMATE,
	gpc::Entities::DERAUMERE,
	gpc::Entities::SIBUR,
	gpc::Entities::MENDIANE,
	gpc::Entities::PHIRAS,
	gpc::Entities::THYSTAME,
};