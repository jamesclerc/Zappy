#pragma once

#include <SFML/Graphics.hpp>
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
		std::string getIp();
		int getPort();
	private:
		void fillString();
		void drawFirst();
		void drawSecond();
		void init_background(std::string path);
		void init_start(std::string path);
		void init_text(std::string path);
		int i;
		sf::Font font;
		sf::Text ip_txt;
		sf::Text port_txt;
		std::string port;
		std::string ip;
		state _state;
		sf::RenderWindow &m_window;
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
