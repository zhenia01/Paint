#pragma once

#include "Tool.h"
#include "ThickLine.h"

namespace Tool {
	class Line :
		public Tool {
	public:
		Line();
		virtual ~Line() {};

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	public:
		sf::Vector2f last;
		float thickness;
		sf::Color color;
		ThickLine line;

	private:
		std::list<ThickLine> _lines;
	};
}
