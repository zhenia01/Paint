#pragma once

#include <SFML/Graphics.hpp>
#include "Test.h"

namespace GUI {
	class Widget :
		public sf::Drawable,
		public sf::Transformable,
		public sf::NonCopyable
	{
	public:

		//using PTR = std::shared_ptr<Widget>;

		Widget() = default;
		virtual ~Widget() = default;

		void setPosition(const sf::Vector2f& pos);
		void setPosition(float x, float y);
		sf::Vector2f getPosition() const;

		virtual sf::Vector2f getSize() const = 0;

		virtual void updateShape();
		virtual bool handleEvent(const sf::Event& event) = 0;

	protected:
		sf::Vector2f _position;
	};
}

