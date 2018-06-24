//
// EPITECH PROJECT, 2018
// GraphicClient.hpp
// File description:
// GraphicClient class
//

#pragma once

#include <vector>

#include "Player.hpp"
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
			void addPlayer(Player p);
			void run();
		private:
			int _timer;
			void runMenu();
			void initConnection();
			void mainLoop();
			sf::RenderWindow *_window;
			static GraphicClient *_instance;
			std::vector<gpc::Player> _players;
			gpc::Menu *_menu;
			Communication _com;
			gpc::Map *_map;
	};
}