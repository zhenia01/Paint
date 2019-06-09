// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Canvas.h"
#include <iostream>

Canvas::Canvas(const sf::Vector2f& position, const sf::Vector2f& size) :
	_size(size), _position(position), _thickness(2.f), _mode(Tool::Mode::Pencil) {

	//_shape.setSize(size);
	//_shape.setPosition(position);
	//_shape.setFillColor(sf::Color::White);
	//_shape.setOutlineColor(sf::Color::Black);
	//_shape.setOutlineThickness(2.f);
}

bool Canvas::handleEvent(const sf::Event& event,const sf::RenderWindow& window) {
	if (event.type == event.MouseButtonPressed) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			_tools[_mode].onPress(event, window);
		}
	} else if (event.type == event.MouseButtonReleased) {
		if (_mode == Tool::Mode::Save) {
			_tools[_mode].onPress(event, window);
			_mode = Tool::Mode::Pencil;
		} else if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			_tools[_mode].onRelease(event, window);
		}

	} else if (event.type == event.MouseMoved) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) })) {
			if (_tools[_mode].status == Tool::Status::Dragging) {
				_tools[_mode].onDrag(event, window);
			} else {
				_tools[_mode].onMove(event, window);
			}
		} else {
			if (_tools[_mode].status == Tool::Status::Dragging) {
				_tools[_mode].onRelease(event, window);
			}
			_tools[_mode].onNothing();
		}
	}

	return true;
}


sf::Vector2f Canvas::getSize() const {
	return _size;
}

void Canvas::setColor(const sf::Color& color) {
	_color = color;
	_tools.setColor(color);
}

void Canvas::setThickness(const float thickness) {
	_thickness = thickness;
	_tools.setThickness(thickness);
}

void Canvas::setMode(Tool::Mode mode) {
	_mode = mode;
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//target.draw(_shape, states);
	_tools.draw(target, states);
}