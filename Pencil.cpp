// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Pencil.h"

Tool::Pencil::Pencil(std::list<std::unique_ptr<sf::Drawable>>& list) : BaseTool(Mode::Pencil), thickness(2.f), outlineColor(sf::Color::Black), _lines(list) {
	onPress = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {
		status = Status::Dragging;

		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

		last = mousePos;
	};

	onRelease = [&](const sf::Event&, const sf::RenderWindow&) mutable {
		status = Status::None;
	};

	onDrag = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {

		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
		sf::Vector2f newLast = mousePos;

		ThickLine line(last + sf::Vector2f(thickness, thickness), newLast + sf::Vector2f(thickness, thickness), thickness, outlineColor);

		_lines.push_back(std::unique_ptr<sf::Drawable>(new ThickLine(last, newLast, thickness, outlineColor)));

		last = newLast;
	};

	onMove = [](const sf::Event&, const sf::RenderWindow&) {};
}

Tool::Pencil::~Pencil() {
}
