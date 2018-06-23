//
// EPITECH PROJECT, 2018
// Player.hpp
// File description:
// Player class
//

#pragma once

#include <vector>

#include "IEntity.hpp"
#include "Ressource.hpp"
#include "Tiles.hpp"

namespace gpc {
	class Player : public IEntity {
		public:
			Player(int x, int y, Entities entity, int playerId, Direction dir, Tiles &tile, int lvl);
			~Player();
			virtual void draw() final;
			virtual void update() final;
			void levelUp();
			void setLevel(int lvl);
			void moveForward();
			void addInInventory(IEntity *entity);
			void deleteInInventory(IEntity *entity);
			void pickToInventory(Entities entitie);
			void dropInventory(Entities entitie);
			void deleteInInventoryByEntities(Entities entitie);

		private:
			int _id;
			int _lvl;
			Direction _direction;
			std::vector<IEntity *> _inventory;
			gpc::Tiles &_currentTile;
	};
}