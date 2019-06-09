#include "Save.h"
#include <array>
#include <exception>
#include <iostream>

Tool::Save::Save(std::list<std::unique_ptr<sf::Drawable>>& list) : _list(list)  {

	onPress = [&](const sf::Event &, const sf::RenderWindow&) mutable {
		sf::RenderTexture texture;
		texture.create(1200+105, 800+160);

		texture.clear(sf::Color::White);
		for (auto& i : _list) {
			texture.draw(*i);
		}
		texture.display();

		int i = 0;
		sf::Image image;
		while (image.loadFromFile("Saved/screenshot" + std::to_string(++i) + ".png"));

		texture.getTexture().copyToImage().saveToFile("Saved/screenshot" + std::to_string(i) + ".png");
	};

	onRelease = [](const sf::Event&, const sf::RenderWindow&) {
	};

	onDrag = [](const sf::Event &, const sf::RenderWindow&) {
	};

	onMove = [](const sf::Event&, const sf::RenderWindow&) {};
	
}
