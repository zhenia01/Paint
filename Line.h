#pragma once

#include "Tool.h"
#include "ThickLine.h"

namespace Tool {
	class Line :
		public Tool {
	public:
		Line() : Tool(Mode::Line), thickness(2.f) {};
		virtual ~Line() {};

	public:
		sf::Vector2f last;
		float thickness;
		sf::Color color;
		ThickLine line;
	};
}
