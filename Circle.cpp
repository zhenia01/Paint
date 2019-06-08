#include "Circle.h"

Tool::Circle::Circle(std::list<std::unique_ptr<sf::Drawable>>& list) : thickness(2.f), color(sf::Color::Black), _circles(list) {
	onPress = [&](const sf::Event & event) mutable {
		if (point.x < 0.1f && point.y < 0.1f) {
			status = Status::Moving;
			point = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };

			_current.setPosition(point);
			_current.setRadius(0.f);
			_current.setOutlineColor(color);
			_current.setOutlineThickness(thickness);
			_current.setFillColor(sf::Color::Transparent);
			_circles.push_back(std::unique_ptr<sf::Drawable>(new sf::CircleShape(_current)));

		} else {
			status = Status::None;
		}
	};

	onRelease = [&](const sf::Event&) mutable {
		if (status == Status::None) {
			point = { 0.f, 0.f };
		} ;
	};

	onDrag = [](const sf::Event&) {

	};

	onMove = [&](const sf::Event & event) mutable {
		if ((point.x > 0.1f && point.y > 0.1f) && !_circles.empty()) {
			sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
			auto diff = newLast - _current.getPosition();
			_current.setRadius((std::sqrtf(diff.x * diff.x + diff.y + diff.y)) / 2);
			_circles.back() = std::unique_ptr<sf::Drawable>(new sf::CircleShape(_current));
		}
	};
}

Tool::Circle::~Circle() {
}
