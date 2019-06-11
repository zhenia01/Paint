// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Erase.h"

Tool::Erase::~Erase() {
}

Tool::Erase::Erase(std::list<std::unique_ptr<sf::Drawable>>& list) : 
	thickness(2.f), _lines(list), fillColor(sf::Color::White) {

	_eraser.setOutlineThickness(1.f);
	_eraser.setFillColor(sf::Color::White);

	onPress = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {
		_eraser.setSize({ thickness * 4.f, thickness * 4.f });
		_eraser.setOrigin(thickness / 2.f, thickness / 2.f);
		_eraser.setOutlineColor(sf::Color::Black);

		status = Status::Dragging;

		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		_eraser.setPosition(mousePos);

		_lines.push_back(std::unique_ptr<sf::Drawable>(new sf::RectangleShape(_eraser)));
	};

	onRelease = [&](const sf::Event&, const sf::RenderWindow&) mutable {
		status = Status::None;
		if (!_lines.empty()) {
			_lines.pop_back();
		}
	};

	onDrag = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {

		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
		sf::Vector2f newLast = mousePos;

		auto pos = _eraser.getPosition();
		auto size = _eraser.getSize();

		sf::Vector2f begin = { pos.x + size.x / 2.f, pos.y };
		sf::Vector2f end = { pos.x + size.x / 2.f,  pos.y + size.y };

		ThickLine line(begin, end, _eraser.getSize().x, fillColor);

		point = newLast;

		_eraser.setPosition(newLast);

		_lines.back() = std::unique_ptr<sf::Drawable>(new ThickLine(line));
		_lines.push_back(std::unique_ptr<sf::Drawable>(new sf::RectangleShape(_eraser)));
		
	};

	onMove = [](const sf::Event&, const sf::RenderWindow&) {};
}
