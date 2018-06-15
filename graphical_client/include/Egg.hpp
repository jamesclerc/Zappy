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
			Egg(int x, int y, Entities entity, int eggId);
			~Egg();
			virtual void draw() final;
			virtual void update() final;

		private:
			int _id;
	};
}