#include <string>

#pragma once

namespace observer {
	class Observer {
		public:
			virtual ~Observer() {};

			virtual void update(std::string) = 0;
			
			virtual void update(void*) const = 0;
	};
}