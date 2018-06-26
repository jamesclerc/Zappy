/*
** EPITECH PROJECT, 2018
** menu.cpp
** File description:
** menu.cpp
*/

#include "menu.hpp"
#include "game.hpp"

gpc::Menu::Menu(sf::RenderWindow &window) : m_window(window)
{
	_state = FIRST;
	i = 0;
	init_background("./graphical_client/sprite/logscreen.jpg");
	init_start("./graphical_client/sprite/press_start.png");
	init_text("./graphical_client/font/Pokemon Classic.ttf");
	cursor("./graphical_client/sprite/dracofeu.png");
	scale = 1.8f;
	sign = false;
}

gpc::Menu::~Menu()
{
}

void gpc::Menu::init_background(std::string path)
{
	image.loadFromFile(path);
	draco.setTexture(image, true);
	draco.setScale(1920.0f / (float)draco.getTexture()->getSize().x,
			1020.0f / (float)draco.getTexture()->getSize().y);
}

void gpc::Menu::init_start(std::string path)
{
	press_start.loadFromFile(path);
	start.setTexture(press_start);
	start.setPosition(300, 830);
	start.setScale(1.8f, 1.8f);
}

void gpc::Menu::init_text(std::string path)
{
	ip = "Ip -> ";
	port = "Port -> ";
	font.loadFromFile(path);
	port_txt.setFont(font);
	port_txt.setString(port);
	port_txt.setCharacterSize(60);
	port_txt.setFillColor(sf::Color::Red);
	port_txt.setStyle(sf::Text::Bold);
	port_txt.setPosition(100 * 1960 / m_window.getSize().x, \
		650 * 1080 / m_window.getSize().y);
	ip_txt.setFont(font);
	ip_txt.setCharacterSize(60);
	ip_txt.setString(ip);
	ip_txt.setFillColor(sf::Color::Red);
	ip_txt.setStyle(sf::Text::Bold);
	ip_txt.setPosition(100, 400);
}

void gpc::Menu::startScale()
{
	if (sign)
		scale = scale + 0.002;
	else if (sign == false)
		scale = scale - 0.002;
	if (scale >= 1.6)
		sign = false;
	else if (scale <= 1.0)
		sign = true;
	start.setScale(scale, scale);
	start.setPosition(660 - (start.getTexture()->getSize().x * scale) / 2, \
			840 - (start.getTexture()->getSize().y * scale) / 2);
}

void gpc::Menu::eventBackground()
{
	if (event.key.code == sf::Keyboard::Enter) {
		_state = SECOND;
		init_background("./graphical_client/sprite/menu.jpg");
	}
}

void gpc::Menu::drawFirst()
{
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (event.type == sf::Event::KeyPressed){
			eventBackground();
		}
	}
	if (_state == FIRST) {
		m_window.draw(draco);
		startScale();
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

void gpc::Menu::cursor(std::string path)
{
	cursorS.loadFromFile(path);
	cursorSprite.setTexture(cursorS);
	cursorSprite.setScale(2.2f, 2.2f);
	cursorSprite.setPosition(1200, 400);
}

void gpc::Menu::ipStringCheck()
{
	if (isprint(static_cast<char>(event.text.unicode)))
		ip += static_cast<char>(event.text.unicode);
}

void gpc::Menu::portStringCheck()
{
	if (isprint(static_cast<char>(event.text.unicode)))
		port += static_cast<char>(event.text.unicode);
}

void gpc::Menu::stringHandle()
{
	if (i % 2 == 0) {
		if (static_cast<char>(event.text.unicode) == '\b' \
			&& ip.size() > 5) {
			ip.erase(ip.end() - 1, ip.end());
		} else {
			ipStringCheck();
		}
	} else {
		if (static_cast<char>(event.text.unicode) == '\b' \
			&& port.size() > 7) {
			port.erase(port.end() - 1, port.end());
		} else {
			portStringCheck();
		}
	}
}

void gpc::Menu::fillString()
{
	if (static_cast<char>(event.text.unicode) == '\t') {
		i++;
		if (i % 2 == 0)
			cursorSprite.setPosition(1200, 400);
		else
			cursorSprite.setPosition(1200, 700);
		return;
	}
	stringHandle();
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
	m_window.draw(cursorSprite);
	m_window.draw(ip_txt);
	m_window.draw(port_txt);
}

bool gpc::Menu::draw()
{
	m_window.clear();
	if (_state == FIRST) {
		drawFirst();
	} else if (_state == SECOND) {
		drawSecond();
	} else {
		return (true);
	}
	m_window.display();
	return (false);
}

// int main(void)
// {
// 	sf::RenderWindow m_window;
// 	m_window.create(sf::VideoMode(1920, 1020, 32), "Menu", sf::Style::Default);
// 	gpc::Menu menu(m_window);
// 	bool x = false;
// 	// sf::SoundBuffer buffer;
// 	// if (!buffer.loadFromFile("./graphical_client/sounds/pokemonMenu.wav"))
// 	// {
// 	// 	std::cout << "Error loading wav" << std::endl;
// 	// }
// 	// sf::Sound sound;
// 	// sound.setBuffer(buffer);
// 	// sound.play();
// 	while (m_window.isOpen() && x == false){
// 		m_window.clear();
// 		x = menu.draw();
// 		m_window.display();
// 	}
// 	gpc::Game game(m_window);
// 	while (m_window.isOpen()) {
// 		m_window.clear();
// 		game.draw();
// 		m_window.display();
// 	}
// }
