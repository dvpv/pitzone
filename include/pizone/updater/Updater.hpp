#ifndef UPDATER_HPP
#define UPDATER_HPP

#include "pizone/event/Event.hpp"
#include <memory>

namespace pizone
{

template<class T>
class Updater
{
  public:
    virtual ~Updater() = 0;

    virtual void update(std::shared_ptr<T> state, std::shared_ptr<Event> event) = 0;
};

} // namespace pizone

#endif // UPDATER_HPP
