#include "Line.h"

Tool::Line::Line() : Tool(Mode::Line), thickness(2.f), color(sf::Color::Black) {

	onPress = [&](const sf::Event & event) mutable {
		if (last.x < 0.1f && last.y < 0.1f) {
			status = Status::Moving;

			sf::Vector2f newLast{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
			last = newLast;

			ThickLine line(newLast, newLast, thickness, color);
			_lines.push_back(line);
		} else {
			status = Status::None;
		}
	};

	onRelease = [&](const sf::Event&) mutable {
		if (status == Status::None) {
			last = { 0.f, 0.f };
		}
	};

	onDrag = [](const sf::Event&) {

	};

	onMove = [&](const sf::Event & event) mutable {
		if (last.x > 0.1f && last.y > 0.1f) {
			if (!_lines.empty()) {
				_lines.back().setEnd({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) });
			}
		}
	};
}

void Tool::Line::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto i : _lines) {
		target.draw(i, states);
	}
}

