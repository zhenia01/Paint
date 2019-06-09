#include "Pencil.h"

Tool::Pencil::Pencil(std::list<std::unique_ptr<sf::Drawable>>& list) : BaseTool(Mode::Pencil), thickness(2.f), color(sf::Color::Black), _lines(list) {
	onPress = [&](const sf::Event & event) mutable {
		status = Status::Dragging;

		last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
	};

	onRelease = [&](const sf::Event&) mutable {
		status = Status::None;
	};

	onDrag = [&](const sf::Event & event) mutable {

		sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

		ThickLine line(last + sf::Vector2f(thickness, thickness), newLast + sf::Vector2f(thickness, thickness), thickness, color);

		_lines.push_back(std::unique_ptr<sf::Drawable>(new ThickLine(last, newLast, thickness, color)));

		last = newLast;
	};

	onMove = [](const sf::Event&) {};
}

Tool::Pencil::~Pencil() {
}
