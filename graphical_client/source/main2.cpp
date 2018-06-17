#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#define Longueur 640
#define Largeur 960

void game(sf::RenderWindow *app)
{
	sf::Texture img_menu;
	img_menu.loadFromFile("menu.jpg");
	sf::Sprite menu;
	menu.setTexture(img_menu);
	menu.setScale((float)app->getSize().x / menu.getTexture()->getSize().x,
			(float)app->getSize().y / menu.getTexture()->getSize().y);
	std::string ip;
	std::string port;
	int i;
	while (app->isOpen()) {
		sf::Event event;
		while (app->pollEvent(event)) {
		        if (event.type == sf::Event::Closed)
	                        app->close();
			if (event.type == sf::Event::TextEntered) {
				if (event.key.code == sf::Keyboard::Tab)
					i++;
				else {
					if (i % 2 == 0) {
						ip += static_cast<char>(event.text.unicode);
					} else {
						port += static_cast<char>(event.text.unicode);
					}
					//printf("ip is -> %s, port is -> %s\n" , ip.c_str(), port.c_str());
				}
			}
		}
		app->clear();
		app->draw(menu);
		//app->draw(text);
		app->display();
	}
	printf("%s     %s\n" , ip.c_str(), port.c_str());
}

int main()
{
	sf::RenderWindow app(sf::VideoMode(960, 640, 32), "Menu", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
	sf::Texture image;
	image.loadFromFile("logscreen.jpg");
	sf::Sprite sprite;
	sprite.setTexture(image);
	sf::Texture image2;
	image2.loadFromFile("press_start.png");
	sf::Sprite btn;
	btn.setTexture(image2);
	btn.setPosition(100, 500);
	sprite.setScale((float)app.getSize().x / sprite.getTexture()->getSize().x,
			(float)app.getSize().y / sprite.getTexture()->getSize().y);
	while(app.isOpen()) {
                sf::Event event;
                while (app.pollEvent(event)) {
		        if (event.type == sf::Event::Closed)
	                        app.close();
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Enter) {
					game(&app);
				}
			}
		}
                app.clear();
                app.draw(sprite);
		app.draw(btn);
		app.display();
	}
	return EXIT_SUCCESS;
}
