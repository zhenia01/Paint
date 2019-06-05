// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Canvas.h"
#include <iostream>

Canvas::Canvas(const sf::Vector2f& position, const sf::Vector2f& size) :
	_size(size), _position(position)
{
	_shape.setSize(size);
	_shape.setPosition(position);
	_shape.setFillColor(sf::Color::White);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(1.f);

	state.mode = PaintState::Mode::Pencil;

	initDrawMap();
}

bool Canvas::handleEvent(const sf::Event& event) {
	if (event.type == event.MouseButtonPressed) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			std::cout << "click" << std::endl;
			_drawMap[state.mode].onClick(event);
		}
	} else if (event.type == event.MouseButtonReleased) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			std::cout << "release" << std::endl;
			_drawMap[state.mode].onRelease(event);
		}

	}else if (event.type == event.MouseMoved) {
		sf::FloatRect rect;
		rect.left = _position.x;
		rect.top = _position.y;
		rect.width = _size.x;
		rect.height = _size.y;
		const sf::Vector2f
			mousePosition(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
		if (rect.contains(mousePosition)) {
			if (_drawMap[state.mode].isPressed) {
				_drawMap[state.mode].onDrag(event);
			} 
		} else {
			_drawMap[state.mode].isPressed = false;
		}
	}

		return true;
}


sf::Vector2f Canvas::getSize() const {
	return _size;
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape, states);

	if (!_linesArray.empty()) {
	for (auto i : _linesArray) {
		target.draw(i, states);
	}
	}
}

void Canvas::initDrawMap() {

	initPencil();


}

void Canvas::initPencil() {
	auto mode = PaintState::Mode::Pencil;
	DrawState stat;
	_drawMap.insert(std::pair<PaintState::Mode, DrawState>(mode, stat));

	_drawMap[PaintState::Mode::Pencil].draw = [copyState = state, copyLines = &_linesArray](const sf::Event &) -> void {
		
	};

	_drawMap[PaintState::Mode::Pencil].onClick = [copyLast = &_lastPoint, copyPressed = &_drawMap[PaintState::Mode::Pencil].isPressed](const sf::Event& event) -> void {
		*copyPressed = !*copyPressed;
		*copyLast = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
	};
	_drawMap[PaintState::Mode::Pencil].onRelease = [copyPressed = &_drawMap[PaintState::Mode::Pencil].isPressed](const sf::Event&) {
		*copyPressed = !*copyPressed;
	};
	_drawMap[PaintState::Mode::Pencil].onMove = [](const sf::Event&) {

	};
	_drawMap[PaintState::Mode::Pencil].onDrag = [copyLast = &_lastPoint, copyState = &state, copyLines = &_linesArray](const sf::Event & event) {
		
		ThickLine line(*copyLast, { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) },
			copyState->thickness, copyState->color);
			
		copyLines->push_back(std::move(line));

		*copyLast = sf::Vector2f{static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

	};
}