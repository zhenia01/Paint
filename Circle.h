#pragma once

#include "Tool.h"

namespace Tool {
	class Circle:
		public Tool{
	public:
		Circle() : Tool(Mode::Circle), thickness(2.f) {};
		virtual ~Circle() {};

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;
		sf::CircleShape circle;
	};
}
