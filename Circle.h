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
		sf::Color color;
		sf::CircleShape circle;

	private:
		//std::unique_ptr<sf::CircleShape> _current;
		sf::CircleShape _current;
		std::list<std::unique_ptr<sf::Drawable>>& _circles;
	};
}
