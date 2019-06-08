#pragma once

#include "BaseTool.h"

namespace Tool {
	class Rectangle:
		public BaseTool{
	public:
		Rectangle(std::list<std::unique_ptr<sf::Drawable>>& list);
		virtual ~Rectangle();

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;

	private:
		sf::RectangleShape _rect;
		std::list<std::unique_ptr<sf::Drawable>>& _rects;
	};
}
