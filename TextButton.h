#pragma once

#include "Button.h"
#include "Label.h"

namespace GUI {
	class TextButton : public Button {
	public:
		TextButton();
		TextButton(const std::string& string,const sf::Vector2f& size, const sf::Font& font);
		virtual ~TextButton();
		
		virtual void setCallBack(FuncType func) override;

		void setText(const std::string& text);
		std::string getText() const;
		void setCharacterSize(unsigned int size);
		void setFont(const sf::Font& font);

		void setTextColor(const sf::Color& color);
		void setFillColor(const sf::Color& color);
		void setOutlineColor(const sf::Color& color);
		void setOutlineThickness(float thickness);

		sf::Color getFillColor() const;

		virtual sf::Vector2f getSize() const override;
		virtual void setSize(const sf::Vector2f& size) override;

		virtual void onClick() override;

		virtual bool handleEvent(const sf::Event& event) override;

	private:
		sf::RectangleShape _shape;
		float _thickness;
		Label _label;
		sf::Color _fillColor;
		sf::Color _outlineColor;
		sf::Clock _time;


	private:
		virtual void updateShape() override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void onMouseEntered() override;
		virtual void onMouseLeft() override;

		void centering();
	};
}
