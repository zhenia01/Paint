// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Tools.h"

Tool::Tools::Tools() : _pencil(_draw), _circle(_draw), 
_line(_draw), _square(_draw),
_rect(_draw), _erase(_draw), _triangle(_draw), 
_poly(_draw), _save(_draw), _poly_5(_draw), _poly_6(_draw){
	
}

Tool::BaseTool Tool::Tools::operator[](Mode mode) const {
	switch (mode) {
	case Mode::None:
		return BaseTool();
		break;
	case Mode::Rectangle:
		return _rect;
		break;
	case Mode::Circle:
		return _circle;
		break;
	case Mode::Triangle:
		return _triangle;
		break;
	case Mode::Line:
		return _line;
		break;
	case Mode::Erase:
		return _erase;
		break;
	case Mode::Pencil:
		return _pencil;
		break;
	case Mode::Poly:
		return _poly;
		break;
	case Mode::Save:
		return _save;
		break;
	case Mode::Square:
		return _square;
		break;
	case Mode::Poly_5:
		return _poly_5;
		break;
	case Mode::Poly_6:
		return _poly_6;
		break;
	default:
		return BaseTool();
		break;
	}
}

void Tool::Tools::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto &i : _draw) {
		target.draw(*i, states);
	}
}

void Tool::Tools::setThickness(const float thickness) {
	_pencil.thickness = thickness;
	_line.thickness = thickness;
	_circle.thickness = thickness;
	_erase.thickness = thickness;
	_rect.thickness = thickness;
	_triangle.thickness = thickness;
	_poly.thickness = thickness;
	_square.thickness = thickness;
	_poly_6.thickness = thickness;
	_poly_5.thickness = thickness;
}

void Tool::Tools::setOutlineColor(const sf::Color& color) {
	_pencil.outlineColor = color;
	_line.outlineColor = color;
	_circle.outlineColor = color;
	_rect.outlineColor = color;
	_triangle.outlineColor = color;
	_poly.outlineColor = color;
	_square.outlineColor = color;
	_poly_6.outlineColor = color;
	_poly_5.outlineColor = color;

}

void Tool::Tools::setFillColor(const sf::Color& color) {
	_circle.fillColor = color;
	_rect.fillColor = color;
	_triangle.fillColor = color;
	_poly.fillColor = color;
	_square.fillColor = color;
	_poly_6.fillColor = color;
	_poly_5.fillColor = color;
}

void Tool::Tools::setFill(bool fill) {
	_triangle.fill = fill;
	_rect.fill = fill;
	_circle.fill = fill;
	_square.fill = fill;
	_poly_5.fill = fill;
	_poly_6.fill = fill;
}

void Tool::Tools::setEraseColor(const sf::Color& color) {
	_erase.fillColor = color;
}

void Tool::Tools::deleteAll() {
	_draw.clear();
}

