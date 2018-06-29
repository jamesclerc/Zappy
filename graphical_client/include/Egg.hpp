//
// EPITECH PROJECT, 2018
// Egg.hpp
// File description:
// Egg class
//

#pragma once

#include <vector>

#include "IEntity.hpp"

namespace gpc {
	class Egg : public IEntity {
		public:
			Egg(int x, int y, gpc::Entities entity, int eggId, sf::RenderTexture &window, std::vector<sf::Sprite> &sprite);
			~Egg();
			void hatching();
			int getId();
			virtual void draw() final;
			virtual void update() final;
		private:
			int _id;
			bool _hatching;
			std::vector<sf::Sprite> &_sprite;
	};
}