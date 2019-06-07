#include "Rectangle.h"

Tool::Rectangle::Rectangle() : Tool(Mode::Rectangle), thickness(2.f), color(sf::Color::Black) {

	onPress = [&](const sf::Event & event) mutable {
		if (point.x < 0.1f && point.y < 0.1f) {
			status = Status::Moving;
			point = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };

			sf::RectangleShape rectangle;
			rectangle.setPosition(point);
			rectangle.setSize({ 0.f, 0.f });
			rectangle.setOutlineColor(color);
			rectangle.setOutlineThickness(thickness);
			rectangle.setFillColor(sf::Color::Transparent);

			_rects.push_back(rectangle);
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

			auto& lastRect = _rects.back();

			auto rectangleBounds = lastRect.getGlobalBounds();

			sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
			auto diff = newLast - lastRect.getPosition();
			lastRect.setSize(diff);
		}
	};
}

Tool::Rectangle::~Rectangle() {
}

void Tool::Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto i : _rects) {
		target.draw(i, states);
	}
}
