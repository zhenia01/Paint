#pragma once
#include "Tool.h"
#include "ThickLine.h"

namespace Tool {
	class Pencil :
		public Tool {
	public:

		Pencil();

		virtual ~Pencil();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		std::list<ThickLine>& getLines() const;

	public:
		sf::Vector2f last;
		float thickness;
		sf::Color color;
	
	private:
		static std::list<ThickLine> _lines;
	};

}
