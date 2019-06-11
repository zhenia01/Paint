#include "Square.h"
#include <cmath>

Tool::Square::Square(std::list<std::unique_ptr<sf::Drawable>>& list) : BaseTool(Mode::Square), thickness(2.f),
color(sf::Color::Black), _squares(list), fill(false) {

	onPress = [&](const sf::Event & event, const sf::RenderWindow & window) mutable {
		if (point.x < 0.1f && point.y < 0.1f) {
			status = Status::Moving;
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			point = mousePos;

			_square.setPosition(point);
			_square.setSize({ 0.f, 0.f });
			_square.setOutlineColor(color);
			if (fill) {
				_square.setFillColor(color);
			} else {
				_square.setFillColor(sf::Color::Transparent);
			}
			_square.setOutlineThickness(thickness);

			_squares.push_back(std::unique_ptr<sf::Drawable>(new sf::RectangleShape(_square)));
		} else {
			status = Status::None;
		}
	};

	onRelease = [&](const sf::Event&, const sf::RenderWindow&) mutable {
		if (status == Status::None) {
			point = { 0.f, 0.f };
		}
	};

	onDrag = [](const sf::Event&, const sf::RenderWindow&) {

	};

	onMove = [&](const sf::Event & event, const sf::RenderWindow & window) mutable {
		if ((point.x > 0.1f && point.y > 0.1f) && !_squares.empty()) {
			sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

			sf::Vector2f newLast = mousePos;
			newLast -= _square.getPosition();

			float min = std::min(newLast.x, newLast.y);
			float size = min / std::sqrtf(2.f);

			_square.setSize(sf::Vector2f(size, size) + sf::Vector2f(thickness, thickness));

			_squares.back() = std::unique_ptr<sf::Drawable>(new sf::RectangleShape(_square));
		}
	};
}

Tool::Square::~Square() {
}