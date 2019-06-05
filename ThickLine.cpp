// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ThickLine.h"

ThickLine::ThickLine() :
	_thickLine(sf::Quads, 4),
	_thickness(0.f),
	_begin(),
	_end(),
	_isThick(true),
	_onePixelLine(sf::Lines, 2)
{
	_color = sf::Color::Black;
	updateLine();
}

ThickLine::ThickLine(const sf::Vector2f& begin, const sf::Vector2f& end, const float thickness,const sf::Color& color) :
	_begin(begin), _end(end), _thickness(thickness), 
	_thickLine(sf::Quads, 4), _onePixelLine(sf::Lines, 2),
	_isThick(false), _color(color)
{
	if (_thickness > 0.1f) {
		_isThick = true;
	}
	updateLine();
}

void ThickLine::setBegin(const sf::Vector2f& begin) {
	_begin = begin;
	updateLine();
}

void ThickLine::setEnd(const sf::Vector2f& end) {
	_end = end;
	updateLine();
}

void ThickLine::setThickness(const float thickness) {
	_thickness = thickness;

	_isThick = (_thickness > 0.1f);

	updateLine();
}

void ThickLine::setColor(const sf::Color& color) {
	_color = color;
}

void ThickLine::updateLine() {

	if (!_isThick) {

		_onePixelLine[0].position = _begin;
		_onePixelLine[1].position = _end;

		_onePixelLine[0].color = _color;
		_onePixelLine[1].color = _color;

	} else {

		_thickLine[0].color = _color;
		_thickLine[1].color = _color;
		_thickLine[2].color = _color;
		_thickLine[3].color = _color;

		const sf::Vector2f midLine = _end - _begin;									// vector between points
		const float length =																				// midLine's length
			std::sqrtf(midLine.x * midLine.x + midLine.y * midLine.y);
		sf::Vector2f normal = midLine / length;											// normal vector
		sf::Vector2f turn{ -normal.y, normal.x };										// normal, turned 90 degrees
		sf::Vector2f vector{ turn * _thickness / 2.f };							// half of a thickness

		// drawing Quad clockwise
		_thickLine[0].position = _begin + vector;
		_thickLine[1].position = _end + vector;
		_thickLine[2].position = _end - vector;
		_thickLine[3].position = _begin - vector;
	}
}

void ThickLine::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	states.transform *= getTransform();

	if (_isThick) {
		target.draw(_thickLine, states);
	} else {
		target.draw(_onePixelLine, states);
	}
}


