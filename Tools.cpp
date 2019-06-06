#include "Tools.h"

void Tool::Tools::initPencil() {
	_pencil.onPress = [&](const sf::Event & event) mutable {
		_pencil.status = Status::Dragging;
		_pencil.last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
	};

	_pencil.onRelease = [&](const sf::Event&) mutable {
		_pencil.status = Status::None;
	};

	_pencil.onDrag = [&, target = &_target](const sf::Event & event) mutable {

		sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

		ThickLine line(_pencil.last, newLast, _pencil.thickness, _pencil.color);

		target->draw(line);

		_pencil.last = newLast;
	};

	_pencil.onMove = [](const sf::Event&) {};
}

Tool::Tools::Tools(sf::RenderWindow& target) : _target(target) {
	initPencil();
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
