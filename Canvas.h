#pragma once

#include "Test.h"
#include "ThickLine.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Canvas : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {

public:
	Canvas(const sf::Vector2f& pos, const sf::Vector2f& size);
	~Canvas() = default;

	bool handleEvent(const sf::Event& event);

	sf::Vector2f getSize() const;

	struct DrawState {

		using VoidFunc = std::function<void()>;
		using EventFunc = std::function<void(const sf::Event&)>;

		DrawState() : onClick([](const sf::Event&) {}), onRelease([](const sf::Event&) {}), onMove([](const sf::Event&) {}),
			onDrag([](const sf::Event&) {}), draw([](const sf::Event&) {}), isPressed(false) {}


		EventFunc onRelease;

		EventFunc onClick;
		EventFunc onMove;
		EventFunc onDrag;
		EventFunc draw;

		bool isPressed;
	};

	struct PaintState {

		PaintState() : thickness(0.f), color(sf::Color::Black), mode(Mode::Pencil) {};

		sf::Color color;
		enum class Mode {
			Rectangle,
			Circle,
			Triangle,
			Line,
			Erase,
			Pencil
		};
		Mode mode;
		float thickness;

	};
	PaintState state;


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void initDrawMap();
	void initPencil();

private:

	std::unordered_map<PaintState::Mode, DrawState> _drawMap;

private:
	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::RectangleShape _shape;

	sf::Vector2f _lastPoint;

	//void onMouseEntered();
	//void onMouseLeft();

	std::list<ThickLine> _linesArray;

};


