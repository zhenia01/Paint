#pragma once

#include "BaseTool.h"

namespace Tool {
	class Circle:
		public BaseTool{
	public:
		Circle(std::list<std::unique_ptr<sf::Drawable>>& list);
		virtual ~Circle();

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color fillColor;
		sf::Color outlineColor;
		sf::CircleShape circle;
		bool fill;

	private:
		sf::CircleShape _current;
		std::list<std::unique_ptr<sf::Drawable>>& _circles;
	};
}
