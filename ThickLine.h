#pragma once
#include <SFML/Graphics.hpp>

class ThickLine :
	public sf::Drawable,
	public sf::Transformable {

public:
	ThickLine();
	ThickLine(const sf::Vector2f& begin, const sf::Vector2f& end, const float thickness, const sf::Color& color);

	void setBegin(const sf::Vector2f& begin);
	void setEnd(const sf::Vector2f& end);

	sf::Vector2f getEnd() const;
	sf::Vector2f getBegin() const;

	void setThickness(const float thickness);
	void setColor(const sf::Color& color);

private:
	sf::VertexArray _thickLine;
	sf::Vector2f _begin;
	sf::Vector2f _end;
	float _thickness;
	sf::Color _color;

	sf::VertexArray _onePixelLine;

	bool _isThick;

private:
	void updateLine();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
