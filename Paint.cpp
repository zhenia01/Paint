// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Paint.h"
#include "Widget.h"
#include <iostream>

Paint::Paint() :
	_window{ sf::VideoMode{ 1200, 800 }, "Paint", sf::Style::Close | sf::Style::Titlebar },
	_canvas({ 105, 160 }, { 1090, 630 }, _window) {
	try {
		_fontManager.load(Fonts::ID::Arial, "Assets/arial.ttf");

		_textureManager.load(Textures::ID::Save, "Assets/save.png");
		_textureManager.load(Textures::ID::Circle, "Assets/circle.png");
		_textureManager.load(Textures::ID::Erase, "Assets/erase.png");
		_textureManager.load(Textures::ID::Line, "Assets/line.png");
		_textureManager.load(Textures::ID::Pencil, "Assets/pencil.png");
		_textureManager.load(Textures::ID::Rectangle, "Assets/rectangle.png");
		_textureManager.load(Textures::ID::Triangle, "Assets/triangle.png");
		_textureManager.load(Textures::ID::Thickness_small, "Assets/thickness_small.png");
		_textureManager.load(Textures::ID::Thickness_medium, "Assets/thickness_medium.png");
		_textureManager.load(Textures::ID::Thickness_big, "Assets/thickness_big.png");


	} catch (std::runtime_error & err) {
		std::cerr << err.what() << std::endl;
		_window.close();
	}

	initColors();
	initTools();
}

void Paint::initTools() {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 5; ++j) {
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
	_tools[6]->setCallBack([this]() {});

	_tools[7]->setTexture(_textureManager.get(Textures::ID::Thickness_small));
	_tools[7]->setCallBack([this]() {
		_canvas.setThickness(2.f); });

	_tools[8]->setTexture(_textureManager.get(Textures::ID::Thickness_medium));
	_tools[8]->setCallBack([this]() {
		_canvas.setThickness(4.f); });

	_tools[9]->setTexture(_textureManager.get(Textures::ID::Thickness_big));
	_tools[9]->setCallBack([this]() {
		_canvas.setThickness(8.f); });
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
		update();
		render();
	}
}

void Paint::render() {
	_window.clear(sf::Color(0xf5, 0xf5, 0xf5));

	for (auto& i : _colors) {
		_window.draw(*i);
	}

	_window.draw(_currentColor);

	for (auto& i : _tools) {
		_window.draw(*i);
	}

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

		_canvas.handleEvent(event);
	}
}

void Paint::update() {
}
