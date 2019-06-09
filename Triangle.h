#pragma once
#include "BaseTool.h"
#include "ThickLine.h"

namespace Tool {
	class Triangle :
		public BaseTool {
	public:
		Triangle(std::list<std::unique_ptr<sf::Drawable>>& list);
		virtual ~Triangle();

	public:
		float thickness;
		sf::Color color;
		sf::Vector2f last;

	private:
		sf::Vector2f start;
		int count;
		ThickLine _line;
		std::list<std::unique_ptr<sf::Drawable>>& _lines;
	};

}
