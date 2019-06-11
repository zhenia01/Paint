// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "Label.h"

GUI::Label::Label() {
}

GUI::Label::Label(const std::string& text, const sf::Vector2f& size, const sf::Font& font) : Widget(){
	_text.setFont(font);
	_text.setString(text);
	_text.setFillColor(sf::Color::Black);
	setSize(size);
}

GUI::Label::~Label() {
}

void GUI::Label::setText(const std::string& text) {
	_text.setString(text);
	updateShape();
}

std::string GUI::Label::getText() const {
	return _text.getString();
}

void GUI::Label::setFont(const sf::Font& font) {
	_text.setFont(font);
}

const sf::Font& GUI::Label::getFont() const {
	return *(_text.getFont());
}

void GUI::Label::setCharacterSize(unsigned int size) {
	if (size < getCharacterSize()) {
		_text.setCharacterSize(size);
		centering();
	}
}

unsigned int GUI::Label::getCharacterSize() const {
	return _text.getCharacterSize();
}

void GUI::Label::setTextColor(const sf::Color& color) {
	_text.setFillColor(color);
}

sf::Vector2f GUI::Label::getSize() const {
	auto rect = _shape.getLocalBounds();
	return sf::Vector2f{ rect.width, rect.height };
}

void GUI::Label::setSize(const sf::Vector2f& size) {
	_shape.setSize(size);
	updateShape();
}

void GUI::Label::updateShape() {

	_text.setCharacterSize(static_cast<unsigned int>(getSize().y));
	auto bounds = getTextBounds();

	if (bounds.width > getSize().x) {
		_text.setCharacterSize(static_cast<unsigned int>((getSize().x * getSize().y) / bounds.width));
	}

	centering();
}

void GUI::Label::centering() {
	auto textRect = getTextBounds();
	_text.setOrigin(textRect.width / 2.f + textRect.left, textRect.height / 2.f + textRect.top);
	_text.setPosition(getSize().x / 2.f, getSize().y / 2.f);
}

sf::FloatRect GUI::Label::getTextBounds() const {
	return _text.getLocalBounds();
}

bool GUI::Label::handleEvent(const sf::Event&) {
	return false;
}

void GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.translate(_position);
	target.draw(_text, states);
}

