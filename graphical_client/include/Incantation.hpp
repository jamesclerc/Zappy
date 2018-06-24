//
// EPITECH PROJECT, 2018
// Incantation.hpp
// File description:
// Incantation class
//

#pragma once

#include <vector>

#include "IEntity.hpp"
#include "Player.hpp"

namespace gpc {
	class Incantation : public IEntity {
		public:
			Incantation(int x, int y, Entities entity);
			~Incantation();
			virtual void draw() final;
			virtual void update() final;
			void addPlayer(Player *p);
			void finish(bool incantationResult);
			gpc::Player *getIncantationPlayer();

		private:
			std::vector<Player *> _players;
	};
}