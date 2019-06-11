#pragma once

#include "BaseTool.h"
#include "Pencil.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Erase.h"
#include "Poly.h"
#include "Triangle.h"
#include "Save.h"
#include "Poly_5.h"
#include "Poly_6.h"
#include "Square.h"

#include <memory>

namespace Tool {
	class Tools {
	public:
		Tools();
		BaseTool operator[](Mode mode) const;

		void draw(sf::RenderTarget&, sf::RenderStates) const;

		void setThickness(const float thickness);
		void setColor(const sf::Color& color);
		void setFill(bool fill);

		void deleteAll();

		std::list<std::unique_ptr<sf::Drawable>> _draw;
	private:
		Pencil _pencil;
		Line _line;
		Circle _circle;
		Rectangle _rect;
		Erase _erase;
		Triangle _triangle;
		Poly _poly;
		Poly_5 _poly_5;
		Poly_6 _poly_6;
		Save _save;
		Square _square;
	};

}

