#pragma once

#include "Tool.h"

namespace Tool {
	class Rectangle:
		public Tool{
	public:
		Rectangle();
		virtual ~Rectangle();

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;
		sf::RectangleShape rect;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		std::list<sf::RectangleShape> _rects;
		//sf::FloatRect _canvasBounds;
	};
}
