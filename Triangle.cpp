#include "Triangle.h"

Tool::Triangle::Triangle(std::list<std::unique_ptr<sf::Drawable>>& list) : _lines(list), count(0), thickness(2.f), color(sf::Color::Black) {
	onPress = [&](const sf::Event & event) mutable {
		
		if (count < 3) {
			status = Status::Moving;

			sf::Vector2f newLast{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
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

	onRelease = [&](const sf::Event&) mutable {
	};

	onDrag = [](const sf::Event&) {

	};

	onMove = [&](const sf::Event & event) mutable {
		if (!_lines.empty() && (count > 0 && count < 3)) {
			_line.setEnd({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) });
			_lines.back() = std::unique_ptr<sf::Drawable>(new ThickLine(_line));
		}
	};
}

Tool::Triangle::~Triangle() {
}

