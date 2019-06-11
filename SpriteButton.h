#pragma once

#include "GUI.h"

namespace GUI {
	class SpriteButton : public Button {
	public:
		SpriteButton();
		SpriteButton(const sf::Vector2f& size, sf::Texture* texture);
		virtual ~SpriteButton() = default;

		virtual void setCallBack(FuncType func) override;
		void setTexture(const sf::Texture& texture);

		virtual sf::Vector2f getSize() const override;
		virtual void setSize(const sf::Vector2f& size) override;

		void setOutlineColor(const sf::Color& color);
		void setOutlineThickness(float thickness);
		float getOutlineThickness() const;

		virtual void onClick() override;

		virtual bool handleEvent(const sf::Event& event) override;

	private:
		sf::RectangleShape _shape;
		sf::Sprite _sprite;
		float _thickness;
		sf::Color _fillColor;
		sf::Color _outlineColor;
		sf::Clock _time;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void onMouseEntered() override;
		virtual void onMouseLeft() override;
	};


}

