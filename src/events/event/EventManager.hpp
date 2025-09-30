#pragma once

#include <concepts>
#include <list>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <algorithm>
#include "Event.hpp"

class EventManager {
    using Listeners = std::list<std::function<void(Event&)>>;
    std::unordered_map<std::type_index, Listeners> m_eventMap {};

public:
    // Fires the associated event for all functions that are awaiting it
    void fire(Event&& event) const {
        const auto it = m_eventMap.find(typeid(event));
        if (it == m_eventMap.end()) return;

        for(auto& listeners = it->second; const auto& function : listeners) function(event);
    }

    // Append the said function to the associated list
    template <typename DerivedEvent> requires std::derived_from<DerivedEvent, Event>
    void add(std::function<void(DerivedEvent&)> listener) {
        auto& list = m_eventMap[typeid(DerivedEvent)];

        // Must type erase the DerivedEvent to Event to store it in the list
        list.emplace_back([listener = std::move(listener)](Event& event) {
            listener(static_cast<DerivedEvent&>(event));
        });
    }

    // Clear all lists in the map
    void clear() {
        m_eventMap.clear();
    }

    // Clear all elements of the Event Manager if it goes out of scope
    ~EventManager() {
        clear();
    }
};
