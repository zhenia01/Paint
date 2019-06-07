#include "Erase.h"

Tool::Erase::~Erase() {
}

Tool::Erase::Erase(std::list<ThickLine>& list) : isActive(false), thickness(2.f), _lines(list){

	_eraser.setOutlineColor(sf::Color::Black);
	_eraser.setOutlineThickness(1.f);
	_eraser.setFillColor(sf::Color::White);

	onPress = [&](const sf::Event & event) mutable {

		isActive = true;

		_eraser.setSize({ thickness * 4.f, thickness * 4.f });
		_eraser.setOrigin(thickness / 2.f, thickness / 2.f);

		status = Status::Dragging;

		_eraser.setPosition({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) });

		point = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
	};

	onRelease = [&](const sf::Event&) mutable {
		isActive = false;
		status = Status::None;
	};

	onDrag = [&](const sf::Event & event) mutable {

		sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
		_eraser.setPosition(newLast);

		sf::Vector2f begin = { _eraser.getPosition().x + _eraser.getSize().x / 2.f, _eraser.getPosition().y };
		sf::Vector2f end = { _eraser.getPosition().x + _eraser.getSize().x / 2.f,  _eraser.getPosition().y + _eraser.getSize().y };

		ThickLine line(begin, end, _eraser.getSize().x, sf::Color::White);

		_lines.push_back(line);

		point = newLast;
	};

	onMove = [](const sf::Event&) {};
}

void Tool::Erase::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	//for (auto i : _lines) {
	//	target.draw(i, states);
	//}
		if (isActive) {
			target.draw(_eraser, states);
		}
}
