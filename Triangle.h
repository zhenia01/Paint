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
		sf::Color fillColor;
		sf::Color outlineColor;
		sf::Vector2f last;
		bool fill;

	private:
		sf::Vector2f start;
		int count;
		ThickLine _line;
		sf::VertexArray _vertex;
		std::list<std::unique_ptr<sf::Drawable>>& _lines;
	};

}
