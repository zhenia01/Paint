#pragma once

#include "BaseTool.h"

namespace Tool {
	class Poly_5 :
		public BaseTool {
	public:
		Poly_5(std::list<std::unique_ptr<sf::Drawable>>& list);
		virtual ~Poly_5();

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;
		bool fill;

	private:
		sf::CircleShape _current;
		std::list<std::unique_ptr<sf::Drawable>>& _circles;
	};
}
