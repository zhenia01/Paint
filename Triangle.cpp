#include "Triangle.h"

Tool::Triangle::Triangle(std::list<std::unique_ptr<sf::Drawable>>& list) : _lines(list), count(0), thickness(2.f), color(sf::Color::Black) {
	onPress = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {
		
		if (count < 3) {
			status = Status::Moving;

			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			sf::Vector2f newLast = mousePos;
			last = newLast;

			if (count == 0) {
				start = newLast;
			}

			_line = ThickLine(newLast, newLast, thickness, color);

			_lines.push_back(std::unique_ptr<sf::Drawable>(new ThickLine(_line)));

			count++;

			if (count == 3) {
				_line = ThickLine(start, last, thickness, color);
				_lines.push_back(std::unique_ptr<sf::Drawable>(new ThickLine(_line)));
				count = 0;
			}

		}
			
	};

	onRelease = [&](const sf::Event&, const sf::RenderWindow&) {
	};

	onDrag = [](const sf::Event&, const sf::RenderWindow&) {

	};

	onMove = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {
		if (!_lines.empty() && (count > 0 && count < 3)) {
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			_line.setEnd(mousePos);
			_lines.back() = std::unique_ptr<sf::Drawable>(new ThickLine(_line));
		}
	};
}

Tool::Triangle::~Triangle() {
}

