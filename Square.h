#pragma once
#include "BaseTool.h"
namespace Tool {
	class Square :
		public BaseTool {
	public:
		Square(std::list<std::unique_ptr<sf::Drawable>>& list);
		virtual ~Square();

	public:
		sf::Vector2f point;
		float thickness;
		sf::Color fillColor;
		sf::Color outlineColor;
		bool fill;

	private:
		sf::RectangleShape _square;
		std::list<std::unique_ptr<sf::Drawable>>& _squares;
	};
}

