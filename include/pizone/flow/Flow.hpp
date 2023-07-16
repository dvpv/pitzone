#ifndef PIZONE_FLOW_HPP
#define PIZONE_FLOW_HPP

#include "pizone/event/Event.hpp"
#include <memory>

namespace pizone
{

template<class T>
class Flow
{
  public:
    virtual ~Flow() = 0;

    virtual void handle_event(std::shared_ptr<T> state, std::shared_ptr<Event> event) = 0;
};

} // namespace pizone
#endif // PIZONE_FLOW_HPP
