/*
** EPITECH PROJECT, 2018
** menu
** File description:
** menu.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

namespace gpc {
	class Menu {
	public:
		enum state{
			FIRST,
			SECOND,
			END
		};
		Menu(sf::RenderWindow &window);
		~Menu();
		bool draw();
		void setState(state s);
		std::string getIp();
		int getPort();
		void reset();
	private:
		void fillString();
		void drawFirst();
		void drawSecond();
		void startScale();
		void init_background(std::string path);
		void eventBackground();
		void portStringCheck();
		void ipStringCheck();
		void stringHandle();
		void init_start(std::string path);
		void init_text(std::string path);
		void cursor(std::string path);
		int i;
		float scale;
		bool sign;
		sf::Font font;
		sf::Text ip_txt;
		sf::Text port_txt;
		std::string port;
		std::string ip;
		state _state;
		sf::RenderWindow &m_window;
		sf::Texture cursorS;
		sf::Sprite cursorSprite;
		sf::Texture image;
		sf::Texture image2;
		sf::Sprite back;
		sf::Texture back2;
		sf::Sprite draco;
		sf::Texture press_start;
		sf::Sprite start;
		sf::Event event;
	};
}
