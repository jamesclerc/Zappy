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
#include "Communication.hpp"
#include "menu.hpp"

namespace gpc {
	class GraphicClient {
		public:
			static GraphicClient *getInstance();
			GraphicClient(const GraphicClient&) = delete;
			GraphicClient& operator=(const GraphicClient&) = delete;
			~GraphicClient();
			void addPlayer(Player p);
			void run();
		private:
			void runMenu();
			void initConnection();
			void mainLoop();
			sf::RenderWindow *_window;
			static GraphicClient *_instance;
			std::vector<gpc::Player> _players;
			GraphicClient(sf::RenderWindow *window, gpc::Menu *menu);
			gpc::Menu *_menu;
			gpc::Communication _com;
			gpc::Map *_map;
	};
}