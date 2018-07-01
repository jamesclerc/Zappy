//
// EPITECH PROJECT, 2018
// GraphicClient.hpp
// File description:
// GraphicClient class
//

#pragma once

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Egg.hpp"
#include "Incantation.hpp"
#include "Map.hpp"
#include "menu.hpp"
#include "Communication.hpp"

namespace gpc {
	class GraphicClient {
		public:
			GraphicClient();
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
			void playerTurn(int n , int dir);
			void incantationFinish(int n, std::string result);
			void eggDie(int n);
			gpc::Incantation *getIncantation(int n);
			void playerDie(int n);
			void finishAll();
			void hatchingEgg(int id);
			gpc::Player *getPlayer(int id);
			void ressourcePop(int x, int y, int i);
			void addIncantation(std::vector<int> incantation);
			void addPlayer(int dir, std::string team, std::vector<int> player);
			void run();
		private:
			int _timer;
			void runMenu();
			int initConnection();
			void mainLoop();
			void initRenderWindow();
			void drawPlayers();
			sf::RenderWindow _window;
			static GraphicClient *_instance;
			std::vector<gpc::Player *> _players;
			std::vector<gpc::Egg *> _eggs;
			std::vector<gpc::Incantation *> _incantations;
			gpc::Menu *_menu;
			Communication _com;
			bool _isDrawable;
			gpc::Map *_map;

			//init vectors players
			void initRenderTexture();
			sf::RenderTexture window_f;

			void initFront();
			sf::Texture front;
			sf::Sprite front_s;

			void initFloor();
			sf::Texture floor;
			sf::Sprite floor_s;

			void initMaterial();
			sf::Texture material_t;
			sf::Texture food_t;
			std::vector<sf::Sprite> _material;

			sf::View view;
			float _scaling;
			bool _view_is_init;
			void initView();
			void handleMoveEvent(sf::Event &event);
			void handleZoomEvent(sf::Event &event);
			void handleEvent(sf::Event &event);

			void initFood(sf::Texture &texture);
			void initLinemate(sf::Texture &texture);
			void initDeraumere(sf::Texture &texture);
			void initSibur(sf::Texture &texture);
			void initMendiane(sf::Texture &texture);
			void initPhiras(sf::Texture &texture);
			void initThystame(sf::Texture &texture);

			void initPlayerSprites();
			void initLevelSprites(sf::IntRect rect);
			std::vector<std::vector<sf::Sprite>> player_sprites;
			sf::Texture player_texture;

			sf::Texture egg_t;
			sf::Texture eggHatch_t;
			void initEgg();
			std::vector<sf::Sprite> _egg;
			void drawEggs();
			void drawHud();
			void changeTilefocus(float x, float y);
			Tiles *_tileFocus;
			void initHud();
			sf::Text _text;
			sf::Font _font;
			void initSound();
			sf::SoundBuffer _buffer;
			sf::Sound _sound;
	};
}

static gpc::Entities entitie[7] = {
	gpc::Entities::FOOD,
	gpc::Entities::LINEMATE,
	gpc::Entities::DERAUMERE,
	gpc::Entities::SIBUR,
	gpc::Entities::MENDIANE,
	gpc::Entities::PHIRAS,
	gpc::Entities::THYSTAME
};
