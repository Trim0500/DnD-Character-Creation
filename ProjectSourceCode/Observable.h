#pragma once

#include <list>
#include "Observer.h"

class Observable {
	public: 
		void attach (Observer* o){_observers->push_back(o);}
		void detach (Observer* o){_observers->remove(o);}
		void notify (){
			// std::list<Observer*>::iterator it;
			for (auto const&i : *_observers){
				i->update((void*)this);
			}
		}
		Observable() {
			_observers = new std::list<Observer*>();
		}

	private:
		std::list<Observer*> *_observers;
};