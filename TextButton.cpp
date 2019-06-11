// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "TextButton.h"

GUI::TextButton::TextButton() : _thickness(0.f) {
}

GUI::TextButton::TextButton(const std::string& text, const sf::Vector2f& size, const sf::Font& font) : _label(text, size, font) {
	_label.setFont(font);
	setFillColor(sf::Color::Cyan);
	_thickness = 5;
	setOutlineThickness(5);
	setOutlineColor(sf::Color::Black);
	setSize(size);
}

void GUI::TextButton::setCallBack(FuncType func) {
	_callback = func;
}
GUI::TextButton::~TextButton() {
}

void GUI::TextButton::setText(const std::string& text) {
	_label.setText(text);
	updateShape();
}
std::string GUI::TextButton::getText() const {
	return _label.getText();
}
void GUI::TextButton::setCharacterSize(unsigned int size) {
	if (size < _label.getCharacterSize()) {
		_label.setCharacterSize(size);
		centering();
	}
}

void GUI::TextButton::setFont(const sf::Font& font) {
	_label.setFont(font);
	updateShape();
}

void GUI::TextButton::setTextColor(const sf::Color& color) {
	_label.setTextColor(color);
}
void GUI::TextButton::setFillColor(const sf::Color& color) {
	_fillColor = color;
	_shape.setFillColor(_fillColor);
}
void GUI::TextButton::setOutlineColor(const sf::Color& color) {
	_outlineColor = color;
	_shape.setOutlineColor(_outlineColor);
}
void GUI::TextButton::setOutlineThickness(float thickness) {
	_thickness = thickness;
	_shape.setOutlineThickness(thickness);
}
sf::Color GUI::TextButton::getFillColor() const {
	return _fillColor;
}
sf::Vector2f GUI::TextButton::getSize()const {
	auto rect = _shape.getGlobalBounds();
	return sf::Vector2f(rect.width, rect.height);
}

void GUI::TextButton::setSize(const sf::Vector2f& size) {
	_label.setSize(size);
	_shape.setSize(size);
	updateShape();
}

void GUI::TextButton::updateShape() {

	_label.setCharacterSize(static_cast<unsigned int>(getSize().y));
	sf::Vector2f bounds = _label.getSize();

	if (bounds.x > getSize().x) {
		_label.setCharacterSize(static_cast<unsigned int>((getSize().x * getSize().y) / bounds.x));
	}

	centering();
}

void GUI::TextButton::centering() {
	auto textRect = _label.getTextBounds();
	_label.setPosition({ (getSize().x - textRect.width) / 2.f, (getSize().y - textRect.height) / 2.f - textRect.top });
}

void GUI::TextButton::onClick() {
	_callback();
	_shape.setOutlineThickness(_thickness + 1);
	_time.restart();
}

bool GUI::TextButton::handleEvent(const sf::Event& event) {
	if (_status == Status::OnClick) {
		if (_time.getElapsedTime().asSeconds() > 0.1) {
			_status = Status::Hover;
			setOutlineThickness(_thickness);
			return false;
		} else return true;
	} else return Button::handleEvent(event);
}

void GUI::TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.translate(_position);
	target.draw(_shape, states);
	target.draw(_label, states);
}

void GUI::TextButton::onMouseEntered() {
	_shape.setFillColor(sf::Color(_fillColor.r, _fillColor.g, _fillColor.b, 100));
	_shape.setOutlineColor(sf::Color(_outlineColor.r, _outlineColor.g, _outlineColor.b, 100));
}

void GUI::TextButton::onMouseLeft() {
	_shape.setOutlineColor(_outlineColor);
	_shape.setFillColor(_fillColor);
}