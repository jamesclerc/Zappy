//
// EPITECH PROJECT, 2018
// Entity.hpp
// File description:
// Entity class
//

#pragma once

#include <vector>

namespace gpc {

	enum Direction{
		NORTH = 0,
		SOUTH = 1,
		WEST = 2,
		EAST = 3
	};

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

		protected:
			int _x;
			int _y;
			Entities _idEntity;
	};
}