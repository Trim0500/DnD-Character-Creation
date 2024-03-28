#include <string>

#pragma once

namespace observer {
	class Observer {
		public:
			virtual ~Observer() {};

			virtual void update(std::string) const = 0;
	};
}