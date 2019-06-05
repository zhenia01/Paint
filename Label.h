#pragma once

#include "Widget.h"
#include "AssetManager.h"
#include "Resources.h"

namespace GUI {
	class Label : public Widget {
	public:
	
		Label();
		Label(const std::string& text, const sf::Vector2f& size, const sf::Font& font);
		virtual ~Label();

		void setText(const std::string& text);
		std::string getText() const;

		void setFont(const sf::Font& font);
		const sf::Font& getFont() const;

		void setTextColor(const sf::Color& color);

		virtual sf::Vector2f getSize() const override;
		void setSize(const sf::Vector2f& size);

		virtual bool handleEvent(const sf::Event& event);

		unsigned int getCharacterSize() const;

		void setCharacterSize(unsigned int size);
		sf::FloatRect getTextBounds() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		virtual void updateShape() override;
		void centering();
		sf::RectangleShape _shape;
		sf::Text _text;
	};
}