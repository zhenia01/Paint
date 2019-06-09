#include "Line.h"

Tool::Line::Line(std::list<std::unique_ptr<sf::Drawable>>& list) : BaseTool(Mode::Line), thickness(2.f), color(sf::Color::Black), _lines(list) {

	onPress = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {
		if (last.x < 0.1f && last.y < 0.1f) {
			status = Status::Moving;

			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

			sf::Vector2f newLast = mousePos;
			last = newLast;

			_line = ThickLine(newLast, newLast, thickness, color);
			
			_lines.push_back(std::unique_ptr<sf::Drawable>(new ThickLine(_line)));
		} else {
			status = Status::None;
		}
	};

	onRelease = [&](const sf::Event&, const sf::RenderWindow&) mutable {
		if (status == Status::None) {
			last = { 0.f, 0.f };
		}
	};

	onDrag = [](const sf::Event&, const sf::RenderWindow&) {

	};

	onMove = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {
		if (last.x > 0.1f && last.y > 0.1f) {
			if (!_lines.empty()) {
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				_line.setEnd(mousePos);
				_lines.back() = std::unique_ptr<sf::Drawable>(new ThickLine(_line));
			}
		}
	};
}