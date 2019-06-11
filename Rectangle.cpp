// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Rectangle.h"

Tool::Rectangle::Rectangle(std::list<std::unique_ptr<sf::Drawable>>& list) : BaseTool(Mode::Rectangle), thickness(2.f), 
outlineColor(sf::Color::Black), fillColor(sf::Color::Black), _rects(list), fill(false) {

	onPress = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {
		if (point.x < 0.1f && point.y < 0.1f) {
			status = Status::Moving;
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			point = mousePos;

			_rect.setPosition(point);
			_rect.setSize({ 0.f, 0.f });
			_rect.setOutlineColor(outlineColor);
			if (fill) {
				_rect.setFillColor(fillColor);
			} else {
				_rect.setFillColor(sf::Color::Transparent);
			}
			_rect.setOutlineThickness(thickness);

			_rects.push_back(std::unique_ptr<sf::Drawable>(new sf::RectangleShape(_rect)));
		} else {
			status = Status::None;
		}
	};

	onRelease = [&](const sf::Event&,const sf::RenderWindow&) mutable {
		if (status == Status::None) {
			point = { 0.f, 0.f };
		}
	};

	onDrag = [](const sf::Event&,const sf::RenderWindow&) {

	};

	onMove = [&](const sf::Event & event, const sf::RenderWindow& window) mutable {
		if ((point.x > 0.1f && point.y > 0.1f) && !_rects.empty()) {
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

			sf::Vector2f newLast = mousePos;
			auto diff = newLast - _rect.getPosition();
			_rect.setSize(diff + sf::Vector2f(thickness, thickness));

			_rects.back() = std::unique_ptr<sf::Drawable>(new sf::RectangleShape(_rect));
		}
	};
}

Tool::Rectangle::~Rectangle() {
}