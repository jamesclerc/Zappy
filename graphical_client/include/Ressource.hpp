//
// EPITECH PROJECT, 2018
// Ressource.hpp
// File description:
// Ressource class
//

#pragma once

#include <vector>

#include "IEntity.hpp"

namespace gpc {
	class Ressource : public IEntity {
		public:
			Ressource(int x, int y, Entities entity, sf::RenderTexture &window, sf::Sprite &sprite);
			~Ressource();
			virtual void draw() final;
			virtual void update() final;

		private:
			sf::Sprite &_sprite;
			std::vector<sf::IntRect> _ressources;
			float _pixel_x;
			float _pixel_y;
	};
}