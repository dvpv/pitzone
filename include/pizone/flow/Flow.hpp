#ifndef PIZONE_FLOW_HPP
#define PIZONE_FLOW_HPP

#include "pizone/event/Event.hpp"
#include <functional>
#include <map>
#include <memory>

namespace pizone
{

template<class StateType, class EventType = Event>
using FlowCallback = std::function<void(std::shared_ptr<StateType>, std::shared_ptr<EventType>)>;

template<class StateType>
class Flow
{
  public:
    explicit Flow(std::map<size_t, FlowCallback<StateType>> callbacks);

    template<class EventType>
    void handle_event(std::shared_ptr<StateType> state, std::shared_ptr<EventType> event) const;

  private:
    const std::map<size_t, FlowCallback<StateType>> callbacks;
};

} // namespace pizone
#endif // PIZONE_FLOW_HPP
