#include "Event.h"


void Event::NotifyHandlers() {
    std::vector<std::unique_ptr<EventHandler>>::iterator func = this->Handlers.begin();
    for (; func != this->Handlers.end(); ++func) {
        if (*func != nullptr) {
            (*(*func))();
        }
    }
}

void Event::AddHandler(const EventHandler& handler) {
    this->Handlers.push_back(std::unique_ptr<EventHandler>(new EventHandler{ handler }));
}

void Event::RemoveHandler(const EventHandler& handler) {
    std::vector<std::unique_ptr<EventHandler>>::iterator to_remove = this->Handlers.begin();
    for (; to_remove != this->Handlers.end(); ++to_remove) {
        if (*(*to_remove) == handler) {
            this->Handlers.erase(to_remove);
            break;
        }
    }
}

void Event::operator()() {
    this->NotifyHandlers();
}

Event& Event::operator+=(const EventHandler& handler) {
    this->AddHandler(handler);

    return *this;
}

Event& Event::operator-=(const EventHandler& handler) {
    this->RemoveHandler(handler);

    return *this;
}