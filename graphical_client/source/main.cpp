/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** main cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#define Longueur 256
#define Largeur 384

const sf::IntRect DOWN(0,0,Largeur/12, Longueur/8); //Rectangle de la fiche de sprite
const sf::IntRect LEFT(0,Longueur/8,Largeur/12 , (Longueur/8));
const sf::IntRect RIGHT(0,Longueur/8 * 2,Largeur/12, Longueur/8);
const sf::IntRect UP(0,Longueur/8 * 3,Largeur/12, Longueur/8);
int main()
{
	sf::RenderWindow app(sf::VideoMode(800, 600, 32), "Zappy zeh", sf::Style::Close | sf::Style::Titlebar); // crée une fenetre
	app.setFramerateLimit(60);
	sf::Texture image; //L'image qui sera mis au sprite
	image.loadFromFile("sprite.png"); // load le sprite via un file
	sf::Sprite sprite; // le sprite
	sprite.setTexture(image); // on ajoute l'image
	sprite.setTextureRect(DOWN); // on choisis le rectangle du sprite calculé plus haut
	int i = 0;
	sf::ContextSettings settings = app.getSettings();
	std::cout << "OpenGL version:"<< settings.majorVersion << "." << settings.minorVersion << std::endl;
	while (app.isOpen()) // Tant que la window est open
	{
		sf::Event event;
		while(app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		i++;
		switch(i) {
		case 1:
			sprite.setTextureRect(UP);
			break;
		case 2:
			sprite.setTextureRect(LEFT);
			break;
		case 3:
			sprite.setTextureRect(RIGHT);
			break;
		case 4:
			sprite.setTextureRect(DOWN);
			i = 0;
			break;
		}
        	app.clear(); // Vide tout le dessin en mémoire
		app.draw(sprite); // draw le sprite actuel
		sprite.move(5,5); // move le sprite
		app.draw(sprite); // redraw le sprite
		app.display(); // Affiche dans la fenetre
	}
	return EXIT_SUCCESS;
}