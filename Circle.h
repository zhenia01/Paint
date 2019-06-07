#pragma once

#include "Tool.h"

namespace Tool {
	class Circle:
		public Tool{
	public:
		Circle();
		virtual ~Circle();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;
		sf::CircleShape circle;

	private:
		std::list<sf::CircleShape> _circles;
	};
}
