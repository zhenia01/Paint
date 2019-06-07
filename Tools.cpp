#include "Tools.h"

Tool::Tools::Tools() : _erase(_pencil.getLines()) {
	
}

Tool::Tool Tool::Tools::operator[](Mode mode) const {
	switch (mode) {
	case Mode::None:
		return Tool();
		break;
	case Mode::Rectangle:
		return _rect;
		break;
	case Mode::Circle:
		return _circle;
		break;
	case Mode::Triangle:
		return Tool();
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
	default:
		return Tool();
		break;
	}
}

void Tool::Tools::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	_pencil.draw(target, states);
	_rect.draw(target, states);
	_line.draw(target, states);
	_circle.draw(target, states);
	_erase.draw(target, states);
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
