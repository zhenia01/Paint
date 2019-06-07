#pragma once

#include "ThickLine.h"
#include "Tools.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

class Canvas : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {

public:
	Canvas(const sf::Vector2f& pos, const sf::Vector2f& size);

	bool handleEvent(const sf::Event& event);

	sf::Vector2f getSize() const;
	void setColor(const sf::Color& color);
	void setThickness(const float thickness);
	void setMode(Tool::Mode mode);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::RectangleShape _shape;

	sf::Vector2f _lastPoint;
	float _thickness;
	sf::Color _color;
	Tool::Mode _mode;

	Tool::Tools _tools;

	
};


