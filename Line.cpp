#include "Line.h"

Tool::Line::Line(std::list<std::unique_ptr<sf::Drawable>>& list) : BaseTool(Mode::Line), thickness(2.f), color(sf::Color::Black), _lines(list) {

	onPress = [&](const sf::Event & event) mutable {
		if (last.x < 0.1f && last.y < 0.1f) {
			status = Status::Moving;

			sf::Vector2f newLast{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
			last = newLast;

			_line = ThickLine(newLast, newLast, thickness, color);
			
			_lines.push_back(std::unique_ptr<sf::Drawable>(new ThickLine(_line)));
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
				_line.setEnd({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) });
				_lines.back() = std::unique_ptr<sf::Drawable>(new ThickLine(_line));
			}
		}
	};
}