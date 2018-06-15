//
// EPITECH PROJECT, 2018
// Entity.hpp
// File description:
// Entity class
//

#pragma once

#include <vector>

#include "Graphic.hpp"

namespace gpc {

	enum Entities{
		FOOD = 0,
		LINEMATE = 1,
		DERAUMERE = 2,
		SIBUR = 3,
		MENDIANE = 4,
		PHIRAS = 5,
		THYSTAME = 6,
		PLAYER = 7,
		EGG = 8,
		INCANTATION = 9
	};

	class IEntity {
		public:
			IEntity(int x, int y);
			virtual ~IEntity();
			virtual void draw();
			virtual void update();
			bool is(Entities entity) const;

		private:
			int _x;
			int _y;
			Graphic _graph;
			Entities _idEntity;
	};
}