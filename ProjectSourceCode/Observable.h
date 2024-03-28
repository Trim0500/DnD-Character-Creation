#pragma once

#include <list>

#include "Observer.h"

using namespace observer;

namespace observable {
	class Observable {
		public: 
			virtual ~Observable() {};

			virtual void Attach (Observer*) = 0;

			virtual void Detach (Observer*) = 0;

			virtual void Notify() = 0;
	};
}