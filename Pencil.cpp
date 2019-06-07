#include "Pencil.h"

std::list<ThickLine> Tool::Pencil::_lines;

Tool::Pencil::Pencil() : Tool(Mode::Pencil), thickness(2.f), color(sf::Color::Black) {
	onPress = [&](const sf::Event & event) mutable {
		status = Status::Dragging;

		last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
	};

	onRelease = [&](const sf::Event&) mutable {
		status = Status::None;
	};

	onDrag = [&](const sf::Event & event) mutable {

		sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

		ThickLine line(last, newLast, thickness, color);

		_lines.push_back(line);

		last = newLast;
	};

	onMove = [](const sf::Event&) {};
}

Tool::Pencil::~Pencil() {
}

void Tool::Pencil::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto i : _lines) {
		target.draw(i, states);
	}
}

std::list<ThickLine>& Tool::Pencil::getLines() const {
	return _lines;
}
