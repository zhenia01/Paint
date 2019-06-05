// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Button.h"

GUI::Button::Button() :
	_callback([](){}),
	_status(Status::None) {
}

GUI::Button::~Button() {}

bool GUI::Button::handleEvent(const sf::Event& event) {
	bool res = false;
	if (event.type == sf::Event::MouseButtonReleased) {
		const sf::Vector2f pos = _position;
		const sf::Vector2f size = getSize();
		sf::FloatRect rect;
		rect.left = pos.x;
		rect.top = pos.y;
		rect.width = size.x;
		rect.height = size.y;
		if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
			onClick();
			_status = Status::OnClick;
			res = true;
		}
	} else if (event.type == sf::Event::MouseMoved) {
		const sf::Vector2f pos = _position;
		const sf::Vector2f size = getSize();
		sf::FloatRect rect;
		rect.left = pos.x;
		rect.top = pos.y;
		rect.width = size.x;
		rect.height = size.y;
		Status old_status = _status;
		_status = Status::None;
		const sf::Vector2f
			mouse_pos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
		if (rect.contains(mouse_pos))
			_status = Status::Hover;
		if ((old_status == Status::Hover) && !(_status ==
			Status::Hover))
			onMouseLeft();
		else if (!(old_status == Status::Hover) && (_status ==
			Status::Hover))
			onMouseEntered();
	}
	return res;
}

void GUI::Button::onClick() {}
