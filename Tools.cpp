#include "Tools.h"

Tool::Tools::Tools() : _pencil(_draw), _circle(_draw), _line(_draw), _rect(_draw), _erase(_draw){
	
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
		return BaseTool();
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
	case Mode::Save:
		return _save;
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
}

void Tool::Tools::setColor(const sf::Color& color) {
	_pencil.color = color;
	_line.color = color;
	_circle.color = color;
	_erase.color = color;
	_rect.color = color;
}
