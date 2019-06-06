#pragma once

#include "Tool.h"

namespace Tool {
	class Erase :
		public Tool {
	public:
		Erase() : Tool(Mode::Circle), thickness(2.f) {};
		virtual ~Erase() {};

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;
		sf::RectangleShape rect;
	};
}