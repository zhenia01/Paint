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
		_textureManager.load(Textures::ID::Rectangle, "Assets/rectangle.png");
		_textureManager.load(Textures::ID::Triangle, "Assets/triangle.png");
		_textureManager.load(Textures::ID::Thick_3px, "Assets/thick_3px.png");
		_textureManager.load(Textures::ID::Thick_5px, "Assets/thick_5px.png");
		_textureManager.load(Textures::ID::Thick_7px, "Assets/thick_7px.png");
		_textureManager.load(Textures::ID::Thick_9px, "Assets/thick_9px.png");
		_textureManager.load(Textures::ID::Zoom_in, "Assets/zoom_in.png");
		_textureManager.load(Textures::ID::Zoom_out, "Assets/zoom_out.png");
		_textureManager.load(Textures::ID::Open, "Assets/open.png");
		_textureManager.load(Textures::ID::Fill, "Assets/fill.png");
		_textureManager.load(Textures::ID::Clear, "Assets/clear.png");


	} catch (std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		_window.close();	
	}

	_icon.loadFromFile("Assets/pencil.png");
	_window.setIcon(64, 64, _icon.getPixelsPtr());

	_shape.setPosition({ 105, 160 });
	_shape.setSize({ 1093, 638 });
	_shape.setFillColor(sf::Color::White);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(2.f);

	_zoom.reset({ 105, 160, 1093, 638 });
	_zoom.setViewport({ 105.f / 1200.f, 160 / 800.f,  1093 / 1200.f, 638 / 800.f });
	_viewSize = _zoom.getSize();

	initColors();
	initTools();
}

void Paint::initTools() {

	for (int i = 0; i < 5; ++i) {
	}

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 6; ++j) {
			std::unique_ptr<GUI::SpriteButton> temp(new GUI::SpriteButton);
			temp->setPosition(270.f + j * 82, 10.f + i * 76);
			temp->setSize({ 64.f, 64.f });
			temp->setOutlineThickness(1);
			temp->setOutlineColor(sf::Color::Black);
			_tools.push_back(std::move(temp));
		}
	}

	_tools[0]->setTexture(_textureManager.get(Textures::ID::Circle));
	_tools[0]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Circle);
		});

	_tools[1]->setTexture(_textureManager.get(Textures::ID::Erase));
	_tools[1]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Erase);
		});

	_tools[2]->setTexture(_textureManager.get(Textures::ID::Line));
	_tools[2]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Line);
		});

	_tools[3]->setTexture(_textureManager.get(Textures::ID::Pencil));
	_tools[3]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Pencil);
		});

	_tools[4]->setTexture(_textureManager.get(Textures::ID::Rectangle));
	_tools[4]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Rectangle);
		});

	_tools[5]->setTexture(_textureManager.get(Textures::ID::Triangle));
	_tools[5]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Triangle);
		});

	_tools[6]->setTexture(_textureManager.get(Textures::ID::Save));
	_tools[6]->setCallBack([this]() {
		_canvas.setMode(Tool::Mode::Save);
		});

	_tools[7]->setTexture(_textureManager.get(Textures::ID::Zoom_in));
	_tools[7]->setCallBack([this]() {
		_zoom.zoom(2.f / 3.f);
		});

	_tools[8]->setTexture(_textureManager.get(Textures::ID::Zoom_out));
	_tools[8]->setCallBack([this]() {
		if (_zoom.getSize().x * 3.f / 2.f <= _viewSize.x) {
			_zoom.zoom(3.f / 2.f);
			if (_zoom.getSize().x >= _viewSize.x - 10) {
				_zoom.reset({ 105, 160, 1093, 638 });
			}
		}
		});

	_tools[9]->setTexture(_textureManager.get(Textures::ID::Open));
	_tools[9]->setCallBack([this]() {
		std::filesystem::path path(std::filesystem::current_path());
		path /= "Input";
		for (auto& i : std::filesystem::directory_iterator(path)) {
			_canvas.loadImage(i.path().string());
		}
		});

	_tools[10]->setTexture(_textureManager.get(Textures::ID::Fill));
	_tools[10]->setCallBack([this]() {
		_canvas.setFill(!_canvas.getFill());
		});

	_tools[11]->setTexture(_textureManager.get(Textures::ID::Clear));
	_tools[11]->setCallBack([this]() {
		_canvas.deleteAll();
		});

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

	_window.draw(_shape);

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