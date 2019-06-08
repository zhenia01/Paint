#include "Rectangle.h"

Tool::Rectangle::Rectangle(std::list<std::unique_ptr<sf::Drawable>>& list) : BaseTool(Mode::Rectangle), thickness(2.f), color(sf::Color::Black), _rects(list) {

	onPress = [&](const sf::Event & event) mutable {
		if (point.x < 0.1f && point.y < 0.1f) {
			status = Status::Moving;
			point = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };

			_rect.setPosition(point);
			_rect.setSize({ 0.f, 0.f });
			_rect.setOutlineColor(color);
			_rect.setOutlineThickness(thickness);
			_rect.setFillColor(sf::Color::Transparent);

			_rects.push_back(std::unique_ptr<sf::Drawable>(new sf::RectangleShape(_rect)));
		} else {
			status = Status::None;
		}
	};

	onRelease = [&](const sf::Event&) mutable {
		if (status == Status::None) {
			point = { 0.f, 0.f };
		}
	};

	onDrag = [](const sf::Event&) {

	};

	onMove = [&](const sf::Event & event) mutable {
		if ((point.x > 0.1f && point.y > 0.1f) && !_rects.empty()) {

			sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
			auto diff = newLast - _rect.getPosition();
			_rect.setSize(diff);

			_rects.back() = std::unique_ptr<sf::Drawable>(new sf::RectangleShape(_rect));
		}
	};
}

Tool::Rectangle::~Rectangle() {
}