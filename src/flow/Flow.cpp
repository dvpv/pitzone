#include "pizone/flow/Flow.hpp"

namespace pizone
{

template<class StateType>
Flow<StateType>::Flow(std::map<size_t, FlowCallback<StateType>> callbacks)
  : callbacks(callbacks)
{
}

template<class StateType>
template<class EventType>
void
Flow<StateType>::handle_event(std::shared_ptr<StateType> state, std::shared_ptr<EventType> event) const
{
    if (callbacks.find(typeid(event).hash_code()) != callbacks.end())
    {
        this->callbacks[typeid(event).hash_code()](state, event);
    }
}

} // namespace pizone