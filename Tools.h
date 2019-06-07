#pragma once

#include "Pencil.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Erase.h"

namespace Tool {
	class Tools {
	public:
		Tools();
		Tool operator[](Mode mode) const;

		void draw(sf::RenderTarget&, sf::RenderStates) const;

		void setThickness(const float thickness);
		void setColor(const sf::Color& color);

	private:
		//void initPencil();
		//void initLine();
		//void initCircle();
		//void initRectangle();
		//void initErase();

	private:
		Pencil _pencil;
		Line _line;
		Circle _circle;
		Rectangle _rect;
		Erase _erase;
	};

}

