#pragma once

#include "Tool.h"
#include "ThickLine.h"

namespace Tool {
	class Erase :
		public Tool {
	public:
		Erase(std::list<ThickLine>& list);
		virtual ~Erase();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color color;
		sf::RectangleShape rect;

	private:
		sf::RectangleShape _eraser;
		std::list<ThickLine>& _lines;
		bool isActive;
	};
}