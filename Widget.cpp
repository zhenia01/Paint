// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "Widget.h"

void GUI::Widget::setPosition(const sf::Vector2f& pos) {
	_position = pos;
}

void GUI::Widget::setPosition(float x, float y) {
	_position.x = x;
	_position.y = y;
}

sf::Vector2f GUI::Widget::getPosition() const {
	return _position;
}

void GUI::Widget::updateShape() {}