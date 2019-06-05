#pragma once

#include "Widget.h"
#include <SFML/Graphics.hpp>
#include <functional>

struct Command {
	//std::function<void(GUI::Widget&)> action;
	unsigned int category;
};

namespace Category {
	enum Type {
		None = 0,
		ColorButton = 1 << 0,
		ShapeButton = 1 << 1,
		ToolButton = 1 << 2
		// TODO: rest categories
	};
}
