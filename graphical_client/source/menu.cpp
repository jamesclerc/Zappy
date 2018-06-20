/*
** EPITECH PROJECT, 2018
** menu.cpp
** File description:
** menu.cpp
*/

#include "menu.hpp"

gpc::Menu::Menu(sf::RenderWindow &window) : m_window(window), _state(FIRST), i(0)
{
	init_background("../sprite/logscreen.jpg");
	init_start("../sprite/press_start.png");
	init_text("../font/Pokemon Classic.ttf");
}

gpc::Menu::~Menu()
{
}

void gpc::Menu::init_background(std::string path)
{
	image.loadFromFile(path);
	draco.setTexture(image, true);
	draco.setScale(static_cast<float>(m_window.getSize().x) / draco.getTexture()->getSize().x,
			static_cast<float>(m_window.getSize().y) / draco.getTexture()->getSize().y);
}

void gpc::Menu::init_start(std::string path)
{
	press_start.loadFromFile(path);
	start.setTexture(press_start);
	start.setPosition(100, 500);
}

void gpc::Menu::init_text(std::string path)
{
	ip = "Ip -> ";
	port = "Port -> ";
	font.loadFromFile(path);
	port_txt.setFont(font);
	port_txt.setString(port);
	port_txt.setCharacterSize(40);
	port_txt.setFillColor(sf::Color::Red);
	port_txt.setStyle(sf::Text::Bold);
	port_txt.setPosition(100, 400);
	ip_txt.setFont(font);
	ip_txt.setCharacterSize(40);
	ip_txt.setString(ip);
	ip_txt.setFillColor(sf::Color::Red);
	ip_txt.setStyle(sf::Text::Bold);
	ip_txt.setPosition(100, 250);
}

void gpc::Menu::drawFirst()
{
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (event.type == sf::Event::KeyPressed){
			if (event.key.code == sf::Keyboard::Enter) {
				_state = SECOND;
				init_background("../sprite/menu.jpg");
			}
		}
	}
	if (_state == FIRST) {
		m_window.draw(draco);
		m_window.draw(start);
	}
}

std::string gpc::Menu::getIp()
{
	ip.erase(0, 6);
	if (ip.empty())
		return (std::string ());
	return (ip);
}

int gpc::Menu::getPort()
{
	port.erase(0, 8);
	if (port.empty())
		return (-1);
	return (std::stoi(port));
}

void gpc::Menu::fillString()
{
	if (static_cast<char>(event.text.unicode) == '\t') {
		i++;
		return;
	}
	if (i % 2 == 0) {
		if (static_cast<char>(event.text.unicode) == '\b' && ip.size() > 5)
			ip.erase(ip.end() - 1, ip.end());
		else
			ip += static_cast<char>(event.text.unicode);
	} else {
		if (static_cast<char>(event.text.unicode) == '\b' && port.size() > 7)
			port.erase(port.end() - 1, port.end());
		else
			port += static_cast<char>(event.text.unicode);
	}
	ip_txt.setString(ip);
	port_txt.setString(port);
}

void gpc::Menu::drawSecond()
{
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (event.type == sf::Event::TextEntered) {
			if (static_cast<char>(event.text.unicode) == '\r')
				_state = END;
			else
				fillString();
		}
	}
	m_window.draw(draco);
	m_window.draw(ip_txt);
	m_window.draw(port_txt);
}

bool gpc::Menu::draw()
{
	if (_state == FIRST) {
		drawFirst();
	} else if (_state == SECOND) {
		drawSecond();
	} else {
		return (true);
	}
	return (false);
}

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(960, 640, 32), "Menu", sf::Style::Default);
	gpc::Menu menu(window);
	bool x = false;
	while (window.isOpen() && x == false){
		window.clear();
		x = menu.draw();
		window.display();
	}
	window.close();
}
