#pragma once

#include "Resources.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include "GUI.h"
#include "Canvas.h"
#include <vector>

class Paint {
public:
	Paint();
	void run();

private:
	void render();
	void processEvents();

	void setIcon();

private:
	sf::RenderWindow _window;

	AssetManager<Fonts::ID, sf::Font> _fontManager;
	AssetManager<Textures::ID, sf::Texture> _textureManager;

	std::vector<std::unique_ptr<GUI::TextButton>> _colors;
	GUI::TextButton _currentFillColor;
	GUI::TextButton _currentOutlineColor;
	bool _fill;
	void initColors();

	std::vector<std::unique_ptr<GUI::SpriteButton>> _tools;
	void initTools();

	Canvas _canvas;

	sf::View _zoom;
	sf::Vector2f _viewSize;
	float _zoomFactor;
	void initZoom();

	sf::RectangleShape _canvasShape;
	void initCanvasShape();

	sf::Image _icon;
};


