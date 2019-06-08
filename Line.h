#pragma once

#include "BaseTool.h"
#include "ThickLine.h"

namespace Tool {
	class Line :
		public BaseTool {
	public:
		Line(std::list<std::unique_ptr<sf::Drawable>>& list);
		virtual ~Line() {};

	public:
		sf::Vector2f last;
		float thickness;
		sf::Color color;

	private:

		ThickLine _line;
		std::list<std::unique_ptr<sf::Drawable>>& _lines;
	};
}
