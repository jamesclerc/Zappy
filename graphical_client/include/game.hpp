/*
** EPITECH PROJECT, 2018
** game
** File description:
** game.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace gpc {
	class Game {
	public:
		Game(sf::RenderWindow &window);
		~Game();
		void draw();
	private:
		void init_image(std::string path, int largeur, int longeur);
	private:
		float scaling;
		int width;
		int height;
		void init_material(std::string path);
		void initLinemate();
		void initDeraumere();
		void initSibur();
		void initMendiane();
		void initPhiras();
		void initThystame();
		void draw_structure(int i, int j);
		sf::Texture structure;
		sf::Sprite structure_s;
		sf::IntRect linemate;
		sf::IntRect deraumere;
		sf::IntRect sibur;
		sf::IntRect mendiane;
		sf::IntRect phiras;
		sf::IntRect thystame;
	private:
		sf::Texture sol;
		sf::Sprite sol_s;
		sf::Color sol_c;
		sf::Texture egg;
		sf::Sprite egg_s;
	private:
		void init_pokemon(std::string path);
		std::vector<sf::IntRect> initCanarticho();
		std::vector<sf::IntRect> initTaurus();
		std::vector<sf::IntRect> initScarabrut();
		std::vector<sf::IntRect> initSecateur();
		std::vector<sf::IntRect> initEletrick();
		std::vector<sf::IntRect> initLangue();
		std::vector<sf::IntRect> initMagmar();
		std::vector<sf::IntRect> initRonflex();
		std::vector<std::vector<sf::IntRect>> _vector;
		sf::Texture pokemon;
		sf::Sprite pokemon_s;
	
	private:
		sf::Texture com;
		sf::Sprite com_s;
	private:
		sf::RenderTexture window_f;
		sf::View view;
		sf::Event event2;
		sf::RenderWindow &m_window;
	private:
		sf::Texture image;
		sf::Sprite background;
		void initBackground(std::string path);
	};
};
