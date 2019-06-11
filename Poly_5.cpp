#include "Poly_5.h"

Tool::Poly_5::Poly_5(std::list<std::unique_ptr<sf::Drawable>>& list) : thickness(2.f), color(sf::Color::Black), _circles(list), fill(false) {
	onPress = [&](const sf::Event & event, const sf::RenderWindow & window) mutable {
		if (point.x < 0.1f && point.y < 0.1f) {

			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

			status = Status::Moving;
			point = mousePos;

			_current = sf::CircleShape(0.0f, 5);
			_current.setPosition(point);
			_current.setRadius(0.f);
			_current.setOutlineColor(color);
			_current.setOutlineThickness(thickness);
			if (fill) {
				_current.setFillColor(color);
			} else {
				_current.setFillColor(sf::Color::Transparent);
			}
			_circles.push_back(std::unique_ptr<sf::Drawable>(new sf::CircleShape(_current)));

		} else {
			status = Status::None;
		}
	};

	onRelease = [&](const sf::Event&, const sf::RenderWindow&)mutable {
		if (status == Status::None) {
			point = { 0.f, 0.f };
		};
	};

	onDrag = [](const sf::Event&, const sf::RenderWindow&) {

	};

	onMove = [&](const sf::Event & event, const sf::RenderWindow & window) mutable {
		if ((point.x > 0.1f && point.y > 0.1f) && !_circles.empty()) {
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			sf::Vector2f newLast = mousePos;
			auto diff = newLast - _current.getPosition();
			_current.setRadius((std::sqrtf(diff.x * diff.x + diff.y + diff.y)) / 2);
			_circles.back() = std::unique_ptr<sf::Drawable>(new sf::CircleShape(_current));
		}
	};
}

Tool::Poly_5::~Poly_5() {
}