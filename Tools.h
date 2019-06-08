#pragma once

#include "BaseTool.h"
#include "Pencil.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Erase.h"
#include "Save.h"

#include <memory>

namespace Tool {
	class Tools {
	public:
		Tools();
		BaseTool operator[](Mode mode) const;

		void draw(sf::RenderTarget&, sf::RenderStates) const;

		void setThickness(const float thickness);
		void setColor(const sf::Color& color);

	private:
		Pencil _pencil;
		Line _line;
		Circle _circle;
		Rectangle _rect;
		Erase _erase;
		Save _save;

		std::list<std::unique_ptr<sf::Drawable>> _draw;
	};

}

