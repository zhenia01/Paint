#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <list>

namespace Tool {

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
		Tool() : mode(Mode::None), status(Status::None), onNothing([this]() {status = Status::None; }) {};
		Tool(Mode mode) : mode(mode), status(Status::None), onNothing([this]() {status = Status::None; }) {};
		virtual ~Tool() {};

	public:
		EventFunc onPress;
		EventFunc onRelease;
		EventFunc onDrag;
		EventFunc onMove;

		VoidFunc onNothing;

		Status status;
		Mode mode;
	};
}