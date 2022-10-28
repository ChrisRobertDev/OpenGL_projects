#pragma once
#include <map>
#include <vector>
#include <utility>
#include <functional>

#include "Event_Enums.h"

//class Observer;
template <typename Event>
class EventHandler
{
public:
	//Container of registered objects
	static std::map < Event, std::vector<std::function<void()>>> observers;

	//Takes in an event type and a function which will trigger on event
	template <typename Observer>
	inline static void registerObserver(const Event& ev, Observer&& observer) {
		observers[ev].push_back(std::forward<Observer>(observer));
	}
	//Calls all functions of members of type ev 
	static void notify(const Event& ev) {
		for (const auto& obs : observers[ev]) obs();
	}
};

template<typename Event>
std::map < Event, std::vector<std::function<void()>>> EventHandler<Event>::observers;