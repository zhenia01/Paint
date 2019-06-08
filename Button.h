#pragma once

#include "Widget.h"
#include <functional>

namespace GUI {
	class Button : public Widget {
	public:

		using FuncType = std::function<void()>;

	public:
		Button();
		virtual ~Button();

		virtual bool handleEvent(const sf::Event& event) override;
	
	protected:
		virtual void onMouseEntered() = 0;
		virtual void onMouseLeft() = 0;
		virtual void setCallBack(FuncType func) = 0;

		virtual void setSize(const sf::Vector2f& size) = 0;

		virtual void onClick();
		
	protected:

		FuncType _callback;
		enum class Status {
			None,
			Hover,
			OnClick
		};
		Status _status;
	};
}

