#pragma once

#include "Tool.h"

namespace Tool {
	class Rectangle:
		public Tool{
	public:
		Rectangle() : Tool(Mode::Rectangle), thickness(2.f) {};
		virtual ~Rectangle() {};

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;
		sf::RectangleShape rect;
	};
}
