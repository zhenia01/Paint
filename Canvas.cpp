// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Canvas.h"
#include <iostream>

Canvas::Canvas(const sf::Vector2f& position, const sf::Vector2f& size) :
	_size(size), _position(position), _thickness(0.f), _mode(Mode::Pencil)
{

	_shape.setSize(size);
	_shape.setPosition(position);
	_shape.setFillColor(sf::Color::White);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(1.f);

	initDrawMap();
}

bool Canvas::handleEvent(const sf::Event& event) {
	if (event.type == event.MouseButtonPressed) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			std::cout << "click" << std::endl;
			_drawMap[_mode]->onPress(event);
		}
	} else if (event.type == event.MouseButtonReleased) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			std::cout << "release" << std::endl;
			_drawMap[_mode]->onRelease(event);
		}

	}else if (event.type == event.MouseMoved) {
		sf::FloatRect rect;
		rect.left = _position.x;
		rect.top = _position.y;
		rect.width = _size.x;
		rect.height = _size.y;
		const sf::Vector2f
			mousePosition(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
		if (rect.contains(mousePosition)) {
			if (_drawMap[_mode]->status == Status::Dragging) {
				_drawMap[_mode]->onDrag(event);
			} else {
				_drawMap[_mode]->onMove(event);
			}
		} else {
			_drawMap[_mode]->status = Status::None;
		}
	}

		return true;
}


sf::Vector2f Canvas::getSize() const {
	return _size;
}

void Canvas::setColor(const sf::Color& color) {
	_color = color;
}

void Canvas::setThickness(const float thickness) {
	_thickness = thickness;
}

void Canvas::setMode(Mode mode) {
	_mode = mode;
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape, states);

	for (auto i : _lines) {
		target.draw(i, states);
	}
}

void Canvas::initDrawMap() {

	initPencil();
	initLine();

}

void Canvas::initPencil() {

	_drawMap.insert(std::pair<Mode, std::unique_ptr<Pencil>>(Mode::Pencil, std::make_unique<Pencil>(std::move(Pencil()))));

	auto& map = _drawMap[Mode::Pencil];
	map->onPress = [&](const sf::Event & event) mutable {
		map->setStatus(Status::Dragging);
		map->last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
	};

	map->onRelease = [&](const sf::Event &) mutable {		
		map->setStatus(Status::None);
	};

	map->onDrag = [&, lines = &_lines](const sf::Event & event) mutable {

		sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

		ThickLine line(map->last, newLast, _thickness, _color);

		lines->push_back(std::move(line));

		map->last = newLast;
	};

	map->onMove = [](const sf::Event&) {};
}

void Canvas::initLine() {

	_drawMap.insert(std::pair<Mode, std::unique_ptr<Tool>>(Mode::Line, std::make_unique<Tool>(std::move(Tool()))));
	auto& map = _drawMap[Mode::Line];

	map->onPress = [&, lines = &_lines](const sf::Event & event) mutable {
		if (map->last.x < 0.1f && map->last.y < 0.1f) {
			map->setStatus(Status::Moving);
			map->last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };

			ThickLine line(map->last, map->last, _thickness, _color);

			lines->push_back(std::move(line));
		} else {
			map->status = Status::None;
		}
	};

	map->onRelease = [&, lines = &_lines](const sf::Event& event) mutable {
		if (map->status == Status::None) {
			sf::Vector2f newLast{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };

			lines->back().setEnd(newLast);

			map->last = { 0.f, 0.f };
		} else {

		}

	};

	map->onDrag = [](const sf::Event&) {

	};

	map->onMove = [&, lines = &_lines](const sf::Event& event) mutable {
		if (map->last.x > 0.1f && map->last.y > 0.1f) {
			if (!lines->empty()) {
				lines->back().setEnd({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) });
			}
		}
	};

}
