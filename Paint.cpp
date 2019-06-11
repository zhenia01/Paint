// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Paint.h"
#include "Widget.h"
#include <iostream>
#include <filesystem>

Paint::Paint() :
	_window{ sf::VideoMode{ 1200, 800 }, "Paint", sf::Style::Close | sf::Style::Titlebar },
	_canvas({ 105, 160 }, { 1093, 638 }),
	_zoomFactor(1.f){
	try {
		_fontManager.load(Fonts::ID::Arial, "Assets/arial.ttf");

		_textureManager.load(Textures::ID::Save, "Assets/save.png");
		_textureManager.load(Textures::ID::Circle, "Assets/circle.png");
		_textureManager.load(Textures::ID::Erase, "Assets/erase.png");
		_textureManager.load(Textures::ID::Line, "Assets/line.png");
		_textureManager.load(Textures::ID::Pencil, "Assets/pencil.png");
		_textureManager.load(Textures::ID::Rectangle, "Assets/rect.png");
		_textureManager.load(Textures::ID::Triangle, "Assets/triangle.png");
		_textureManager.load(Textures::ID::Thick_1px, "Assets/thick_1px.png");
		_textureManager.load(Textures::ID::Thick_3px, "Assets/thick_3px.png");
		_textureManager.load(Textures::ID::Thick_5px, "Assets/thick_5px.png");
		_textureManager.load(Textures::ID::Thick_7px, "Assets/thick_7px.png");
		_textureManager.load(Textures::ID::Thick_9px, "Assets/thick_9px.png");
		_textureManager.load(Textures::ID::Zoom_in, "Assets/zoom_in.png");
		_textureManager.load(Textures::ID::Zoom_out, "Assets/zoom_out.png");
		_textureManager.load(Textures::ID::Open, "Assets/open.png");
		_textureManager.load(Textures::ID::Fill, "Assets/fill.png");
		_textureManager.load(Textures::ID::Clear, "Assets/clear.png");
		_textureManager.load(Textures::ID::Poly, "Assets/poly.png");
		_textureManager.load(Textures::ID::Square, "Assets/square.png");
		_textureManager.load(Textures::ID::Poly_5, "Assets/poly_5.png");
		_textureManager.load(Textures::ID::Poly_6, "Assets/poly_6.png");

	} catch (std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		_window.close();	
	}

	setIcon();

	initCanvasShape();
	initZoom();

	initColors();
	initTools();
}

void Paint::initTools() {

	// tools
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 8; ++j) {
			std::unique_ptr<GUI::SpriteButton> temp(new GUI::SpriteButton);
			temp->setPosition(270.f + j * 82, 10.f + i * 76);
			temp->setSize({ 64.f, 64.f });
			temp->setOutlineThickness(1);
			temp->setOutlineColor(sf::Color::Black);
			_tools.push_back(std::move(temp));
		}
	}

	_tools[3]->setOutlineThickness(3);

	_tools[0]->setTexture(_textureManager.get(Textures::ID::Circle));
	_tools[0]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Circle);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[0]->setOutlineThickness(3);
		});

	_tools[1]->setTexture(_textureManager.get(Textures::ID::Erase));
	_tools[1]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Erase);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[1]->setOutlineThickness(3);
		});

	_tools[2]->setTexture(_textureManager.get(Textures::ID::Line));
	_tools[2]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Line);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[2]->setOutlineThickness(3);
		});

	_tools[3]->setTexture(_textureManager.get(Textures::ID::Pencil));
	_tools[3]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Pencil);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[3]->setOutlineThickness(3);
		});

	_tools[4]->setTexture(_textureManager.get(Textures::ID::Rectangle));
	_tools[4]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Rectangle);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[4]->setOutlineThickness(3);
		});

	_tools[5]->setTexture(_textureManager.get(Textures::ID::Square));
	_tools[5]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Square);
		for (size_t i = 0; i <= 7; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[5]->setOutlineThickness(3);
		});

	_tools[6]->setTexture(_textureManager.get(Textures::ID::Triangle));
	_tools[6]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Triangle);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[6]->setOutlineThickness(3);
		});

	_tools[7]->setTexture(_textureManager.get(Textures::ID::Poly));
	_tools[7]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Poly);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[7]->setOutlineThickness(3);
		});

	_tools[8]->setTexture(_textureManager.get(Textures::ID::Poly_5));
	_tools[8]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Poly_5);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[8]->setOutlineThickness(3);
		});

	_tools[9]->setTexture(_textureManager.get(Textures::ID::Poly_6));
	_tools[9]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Poly_6);
		for (size_t i = 0; i <= 9; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[9]->setOutlineThickness(3);
		});

	_tools[10]->setTexture(_textureManager.get(Textures::ID::Fill));
	_tools[10]->setCallBack([this]() {
		_canvas.setFill(!_canvas.getFill());
		_tools[10]->setOutlineThickness((_tools[7]->getOutlineThickness() < 2.f ? 3.f : 1.f));
		});

	_tools[11]->setTexture(_textureManager.get(Textures::ID::Zoom_in));
	_tools[11]->setCallBack([this]() {
		_zoom.zoom(2.f / 3.f);
		});

	_tools[12]->setTexture(_textureManager.get(Textures::ID::Zoom_out));
	_tools[12]->setCallBack([this]() {
		if (_zoom.getSize().x * 3.f / 2.f <= _viewSize.x) {
			_zoom.zoom(3.f / 2.f);
			if (_zoom.getSize().x >= _viewSize.x - 10) {
				_zoom.reset({ 105, 160, 1093, 638 });
			}
		}
		});

	_tools[13]->setTexture(_textureManager.get(Textures::ID::Save));
	_tools[13]->setCallBack([this]() {
		_canvas.save();
		});

	_tools[14]->setTexture(_textureManager.get(Textures::ID::Open));
	_tools[14]->setCallBack([this]() {
		std::filesystem::path path(std::filesystem::current_path());
		path /= "Input";
		for (auto& i : std::filesystem::directory_iterator(path)) {
			_canvas.loadImage(i.path().string());
		}
		});


	_tools[15]->setTexture(_textureManager.get(Textures::ID::Clear));
	_tools[15]->setCallBack([this]() {
		_canvas.deleteAll();
		});

	// thickness
	for (int i = 0; i < 5; ++i) {
		std::unique_ptr<GUI::SpriteButton> temp(new GUI::SpriteButton);
		temp->setPosition(15.f, 585.f + 40*i);
		temp->setSize({ 70.f, 30.f });
		temp->setOutlineThickness(1);
		temp->setOutlineColor(sf::Color::Black);
		_tools.push_back(std::move(temp));
	}

	_tools[16]->setOutlineThickness(3);

	_tools[16]->setTexture(_textureManager.get(Textures::ID::Thick_1px));
	_tools[16]->setCallBack([this]() {
		_canvas.setThickness(1.f);
		for (size_t i = 14; i <= 20; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[16]->setOutlineThickness(3);
		});

	_tools[17]->setTexture(_textureManager.get(Textures::ID::Thick_3px));
	_tools[17]->setCallBack([this]() {
		_canvas.setThickness(3.f);
		for (size_t i = 14; i <= 20; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[17]->setOutlineThickness(3);
		});

	_tools[18]->setTexture(_textureManager.get(Textures::ID::Thick_5px));
	_tools[18]->setCallBack([this]() {
		_canvas.setThickness(5.f);
		for (size_t i = 14; i <= 20; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[18]->setOutlineThickness(3);
		});

	_tools[19]->setTexture(_textureManager.get(Textures::ID::Thick_7px));
	_tools[19]->setCallBack([this]() {
		_canvas.setThickness(7.f);
		for (size_t i = 14; i <= 20; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[19]->setOutlineThickness(3);
		});

	_tools[20]->setTexture(_textureManager.get(Textures::ID::Thick_9px));
	_tools[20]->setCallBack([this]() {
		_canvas.setThickness(9.f);
		for (size_t i = 14; i <= 20; ++i) {
			_tools[i]->setOutlineThickness(1);
		}
		_tools[20]->setOutlineThickness(3);
		});
}

void Paint::initZoom() {
	_zoom.reset({ 105, 160, 1093, 638 });
	_zoom.setViewport({ 105.f / 1200.f, 160 / 800.f,  1093 / 1200.f, 638 / 800.f });
	_viewSize = _zoom.getSize();
}

void Paint::initCanvasShape() {
	_canvasShape.setPosition({ 105, 160 });
	_canvasShape.setSize({ 1093, 638 });
	_canvasShape.setFillColor(sf::Color::White);
	_canvasShape.setOutlineColor(sf::Color::Black);
	_canvasShape.setOutlineThickness(2.f);
}

void Paint::initColors() {

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 2; ++j) {
			std::unique_ptr<GUI::TextButton> temp(new GUI::TextButton);
			temp->setPosition(15.f + j * 40, 160.f + i * 40);
			temp->setSize({ 30.f, 30.f });
			temp->setOutlineThickness(1);
			temp->setOutlineColor(sf::Color::Black);
			_colors.push_back(std::move(temp));
		}
	}

	for (auto& i : _colors) {
		i->setCallBack([this, &i]() {
			_canvas.setColor(i->getFillColor());
			_currentColor.setFillColor(i->getFillColor());
			});
	}

	_currentColor.setSize({ 70.f, 70.f });
	_currentColor.setFillColor(sf::Color::Black);
	_currentColor.setPosition({ 15.f, 490.f });
	_currentColor.setOutlineThickness(1);
	_currentColor.setOutlineColor(sf::Color::Black);

	_colors[0]->setFillColor(sf::Color(0x80, 0x00, 0x00));
	_colors[1]->setFillColor(sf::Color(0xff, 0x00, 0x00));
	_colors[2]->setFillColor(sf::Color(0xff, 0xa5, 0x00));
	_colors[3]->setFillColor(sf::Color(0xff, 0xff, 0x00));
	_colors[4]->setFillColor(sf::Color(0x80, 0x80, 0x00));
	_colors[5]->setFillColor(sf::Color(0x80, 0x00, 0x80));
	_colors[6]->setFillColor(sf::Color(0xff, 0x00, 0xff));
	_colors[7]->setFillColor(sf::Color(0x00, 0xff, 0x00));
	_colors[8]->setFillColor(sf::Color(0x00, 0x80, 0x00));
	_colors[9]->setFillColor(sf::Color(0x00, 0xff, 0xff));
	_colors[10]->setFillColor(sf::Color(0x00, 0x00, 0xff));
	_colors[11]->setFillColor(sf::Color(0x00, 0x00, 0x80));
	_colors[12]->setFillColor(sf::Color(0x00, 0x00, 0x00));
	_colors[13]->setFillColor(sf::Color(0x80, 0x80, 0x80));
	_colors[14]->setFillColor(sf::Color(0xc0, 0xc0, 0xc0));
	_colors[15]->setFillColor(sf::Color(0xff, 0xff, 0xff));
}

void Paint::run() {
	while (_window.isOpen()) {
		processEvents();
		render();
	}
}

void Paint::render() {
	_window.clear(sf::Color(0xf5, 0xf5, 0xf5));

	_window.setView(_window.getDefaultView());

	_window.draw(_canvasShape);

	for (auto& i : _colors) {
		_window.draw(*i);
	}

	_window.draw(_currentColor);

	for (auto& i : _tools) {
		_window.draw(*i);
	}

	_window.setView(_zoom);

	_window.draw(_canvas);

	_window.display();
}

void Paint::processEvents() {

	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			_window.close();
			return;
		}

		for (auto& i : _colors) {
			if (i->handleEvent(event)) {
				break;
			}
		}

		for (auto& i : _tools) {
			if (i->handleEvent(event)) {
				break;
			}
		}

		_canvas.handleEvent(event, _window);

		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::Right: {
				if ((_zoom.getCenter().x + (_zoom.getSize().x / 2.f)) < (105 + 1093)) {
					_zoom.move({ 50, 0 });
				}
					break;
			}
			case sf::Keyboard::Left: {
				if ((_zoom.getCenter().x - (_zoom.getSize().x / 2.f)) > 105) {
					_zoom.move({ -50, 0 });
				}
					break;
			}
			case sf::Keyboard::Up: {
				if (((_zoom.getCenter().y - (_zoom.getSize().y / 2.f))) > 160) {
					_zoom.move({ 0, -50 });
				}
					break;
			}
			case sf::Keyboard::Down: {
				if (((_zoom.getCenter().y + (_zoom.getSize().y / 2.f))) < (160 + 630)) {
					_zoom.move({ 0 , 50 });
				}
					break;
			}
			}
		}
	}
}

void Paint::setIcon() {
	_icon.loadFromFile("Assets/pencil.png");
	_window.setIcon(64, 64, _icon.getPixelsPtr());
}
