#pragma once

#include "BaseTool.h"

namespace Tool {
	class Save :
		public BaseTool {
	public:
		
		Save(std::list<std::unique_ptr<sf::Drawable>>& list);

	private:
		std::list<std::unique_ptr<sf::Drawable>>& _list;
	};
}

