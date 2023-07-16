#ifndef UPDATER_HPP
#define UPDATER_HPP

#include "pizone/event/Event.hpp"
#include <cstdlib>
#include <functional>
#include <map>
#include <memory>

namespace pizone
{

template<class StateType, class EventType = Event>
using UpdaterCallback = std::function<void(std::shared_ptr<StateType>, std::shared_ptr<EventType>)>;

template<class StateType>
class Updater
{
  public:
    explicit Updater(const std::map<size_t, UpdaterCallback<StateType>>& callbacks);

    template<class EventType>
    void update(std::shared_ptr<StateType> state, std::shared_ptr<EventType> event) const;

  private:
    const std::map<size_t, UpdaterCallback<StateType>> callbacks;
};

} // namespace pizone

#endif // UPDATER_HPP
