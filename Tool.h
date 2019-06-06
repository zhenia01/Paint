#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <list>

enum class Status {
	None,
	Moving,
	Dragging
};

enum class Mode {
	None,
	Rectangle,
	Circle,
	Triangle,
	Line,
	Erase,
	Pencil
};

class Tool {

public:	
	using VoidFunc = std::function<void()>;
	using EventFunc = std::function<void(const sf::Event&)>;
	
public:
	Tool() : _mode(Mode::None), status(Status::None) {};
	Tool(Mode mode) : _mode(mode), status(Status::None) {};
	virtual ~Tool() {};

	EventFunc onPress;
	EventFunc onRelease;
	EventFunc onDrag;
	EventFunc onMove;


	void setStatus(Status s) { status = s; }
	Status status;

	sf::Vector2f last;
	
protected:
	Mode _mode;
	
};