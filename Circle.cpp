#include "Circle.h"

Tool::Circle::Circle() : thickness(2.f), color(sf::Color::Black) {
	onPress = [&](const sf::Event & event) mutable {
		if (point.x < 0.1f && point.y < 0.1f) {
			status = Status::Moving;
			point = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };

			sf::CircleShape circle;
			circle.setPosition(point);
			circle.setRadius(0.f);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(thickness);
			circle.setFillColor(sf::Color::Transparent);

			_circles.push_back(circle);
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
		if ((point.x > 0.1f && point.y > 0.1f) && !_circles.empty()) {

			auto& lastCircle = _circles.back();

			sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
			auto diff = newLast - lastCircle.getPosition();
			lastCircle.setRadius((std::sqrtf(diff.x * diff.x + diff.y + diff.y)) / 2);
		}
	};
}

Tool::Circle::~Circle() {
}

void Tool::Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto i : _circles) {
		target.draw(i, states);
	}
}
