// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Canvas.h"
#include <iostream>

Canvas::Canvas(const sf::Vector2f& position, const sf::Vector2f& size) :
	_size(size), _position(position), _mode(Tool::Mode::Pencil), _fill(false) {
}

bool Canvas::handleEvent(const sf::Event& event,const sf::RenderWindow& window) {
	if (event.type == event.MouseButtonPressed) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			_tools[_mode].onPress(event, window);
		}
	} else if (event.type == event.MouseButtonReleased) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
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
		}
	} else if (_mode == Tool::Mode::Poly &&(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter)) {
		_tools[Tool::Mode::Poly].onNothing();
	}

	return true;
}


sf::Vector2f Canvas::getSize() const {
	return _size;
}

void Canvas::setFillColor(const sf::Color& color) {
	_tools.setFillColor(color);
}

void Canvas::setOutlineColor(const sf::Color& color) {
	_tools.setOutlineColor(color);
}

void Canvas::setThickness(const float thickness) {
	_tools.setThickness(thickness);
}

void Canvas::setMode(Tool::Mode mode) {
	_mode = mode;
}

void Canvas::setFill(bool fill) {
	_fill = fill;
	_tools.setFill(true);
}

bool Canvas::getFill() const {
	return _fill;
}

void Canvas::loadImage(const std::string& path) {
	_tools.deleteAll();
	_imageTexture.loadFromFile(path);
	_sprite.setTexture(_imageTexture, true);
	_sprite.setPosition(105, 160);

	_tools._draw.push_front(std::unique_ptr<sf::Drawable>(new sf::Sprite(_sprite)));
}

void Canvas::deleteAll() {
	_tools.deleteAll();
}

void Canvas::save() const {
	_tools[Tool::Mode::Save].onPress(sf::Event(), sf::RenderWindow());
}

void Canvas::setEraseColor(const sf::Color& color) {
	_tools.setEraseColor(color);
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	_tools.draw(target, states);
}