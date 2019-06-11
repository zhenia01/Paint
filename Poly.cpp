#include "Poly.h"

Tool::Poly::Poly(std::list<std::unique_ptr<sf::Drawable>>& list) : _polies(list), count(0),
thickness(2.f), color(sf::Color::Black), fill(false), _vertex(sf::LineStrip) {
	onPress = [&](const sf::Event & event, const sf::RenderWindow & window) mutable {

		status = Status::Moving;

		_vertex.resize(_vertex.getVertexCount() + 1);

		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		sf::Vector2f newLast = mousePos;
		last = newLast;

		_vertex[count].position = newLast;

		if (fill) {
			_vertex[count].color = color;
		} else {
			_vertex[count].color = sf::Color::Transparent;
		}
		if (count == 0) {
			start = newLast;
		}

		_line = ThickLine(newLast, newLast, thickness, color);

		_polies.push_back(std::unique_ptr<sf::Drawable>(new ThickLine(_line)));

		count++;


	};

	onRelease = [](const sf::Event&, const sf::RenderWindow&) {
	};

	onDrag = [](const sf::Event&, const sf::RenderWindow&) {

	};

	onMove = [&](const sf::Event & event, const sf::RenderWindow & window) mutable {
		if (!_polies.empty() && count > 0) {
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			_line.setEnd(mousePos);
			_polies.back() = std::unique_ptr<sf::Drawable>(new ThickLine(_line));
		}
	};

	onNothing = [&]() {

		if (status == Status::Moving) {

			_polies.pop_back();
			//_vertex.resize(_vertex.getVertexCount() + 1);
			_vertex[_vertex.getVertexCount() - 1].position = start;
			if (fill) {
				_vertex[_vertex.getVertexCount() - 1].color = color;
			} else {
				_vertex[_vertex.getVertexCount() - 1].color = sf::Color::Transparent;
			}
			_line = ThickLine(start, last, thickness, color);

			_polies.push_back(std::unique_ptr<sf::Drawable>(new sf::VertexArray(_vertex)));
			_polies.push_back(std::unique_ptr<sf::Drawable>(new ThickLine(_line)));

			_vertex.clear();
			count = 0;
			status = Status::None;
		}
	};
}

Tool::Poly::~Poly() {
}
