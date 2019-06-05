// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "SpriteButton.h"
#include <memory>

GUI::SpriteButton::SpriteButton() : _thickness(0) {
	_shape.setFillColor(sf::Color::White);
	_fillColor = sf::Color::White;
}

GUI::SpriteButton::SpriteButton(const sf::Vector2f& size, sf::Texture* texture) {
	SpriteButton();
	_shape.setSize(size);
	_sprite.setTexture(*texture);
}

void GUI::SpriteButton::setCallBack(FuncType func) {
	_callback = func;
}

void GUI::SpriteButton::setTexture(const sf::Texture& texture) {
	_shape.setTexture(&texture);
}

sf::Vector2f GUI::SpriteButton::getSize() const {
	return _shape.getSize();
}

void GUI::SpriteButton::setSize(const sf::Vector2f& size) {
	_shape.setSize(size);
}

void GUI::SpriteButton::setOutlineColor(const sf::Color& color) {
	_shape.setOutlineColor(color);
}

void GUI::SpriteButton::setOutlineThickness(float thickness) {
	_shape.setOutlineThickness(thickness);
	_thickness = thickness;
}

void GUI::SpriteButton::onClick() {
	_callback();
	_shape.setOutlineThickness(_thickness + 1);
	_time.restart();
}

bool GUI::SpriteButton::handleEvent(const sf::Event& event) {
	if (_status == Status::OnClick) {
		if (_time.getElapsedTime().asSeconds() > 0.1) {
			_status = Status::Hover;
			setOutlineThickness(_thickness);
			return false;
		}
		return true;
	} else return Button::handleEvent(event);
}

void GUI::SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.translate(_position);
	target.draw(_shape, states);
	target.draw(_sprite, states);
}

void GUI::SpriteButton::onMouseEntered() {
	_shape.setFillColor(sf::Color(_fillColor.r, _fillColor.g, _fillColor.b, 150));
	_shape.setOutlineColor(sf::Color(_outlineColor.r, _outlineColor.g, _outlineColor.b, 150));
}

void GUI::SpriteButton::onMouseLeft() {
	_shape.setOutlineColor(_outlineColor);
	_shape.setFillColor(_fillColor);
}

