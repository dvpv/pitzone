#include "pizone/updater/Updater.hpp"

namespace pizone
{

template<class StateType>
Updater<StateType>::Updater(const std::map<size_t, UpdaterCallback<StateType>>& callbacks)
  : callbacks(callbacks)
{
}

template<class StateType>
template<class EventType>
void
Updater<StateType>::update(std::shared_ptr<StateType> state, std::shared_ptr<EventType> event) const
{
    if (callbacks.find(typeid(event).hash_code()) != callbacks.end())
    {
        this->callbacks[typeid(event).hash_code()](state, event);
    }
}

} // namespace pizone