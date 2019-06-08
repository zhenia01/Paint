#pragma once

#include "BaseTool.h"
#include "ThickLine.h"

namespace Tool {
	class Erase :
		public BaseTool {
	public:
		Erase(std::list<std::unique_ptr<sf::Drawable>>& list);
		virtual ~Erase();

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;
		sf::RectangleShape rect;

	private:
		sf::RectangleShape _eraser;
		std::list<std::unique_ptr<sf::Drawable>>& _lines;
	};
}