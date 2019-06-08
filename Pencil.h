#pragma once
#include "BaseTool.h"
#include "ThickLine.h"

namespace Tool {
	class Pencil :
		public BaseTool {
	public:

		Pencil(std::list<std::unique_ptr<sf::Drawable>>& list);

		virtual ~Pencil();

	public:
		sf::Vector2f last;
		float thickness;
		sf::Color color;
	
	private:
		std::list<std::unique_ptr<sf::Drawable>>& _lines;
	};

}
