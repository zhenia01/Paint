#pragma once

#include "BaseTool.h"

namespace Tool {
	class Poly_6 :
		public BaseTool{
	public:
		Poly_6(std::list<std::unique_ptr<sf::Drawable>>& list);
		virtual ~Poly_6();

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color fillColor;
		sf::Color outlineColor;
		bool fill;

	private:
		sf::CircleShape _current;
		std::list<std::unique_ptr<sf::Drawable>>& _circles;
	};

}
