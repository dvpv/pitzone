#ifndef PIZONE_STORE_HPP
#define PIZONE_STORE_HPP

#include "pizone/event/Event.hpp"
#include "pizone/flow/Flow.hpp"
#include "pizone/updater/Updater.hpp"

#include <boost/asio.hpp>

#include <memory>
#include <queue>
#include <vector>

namespace pizone
{

template<class T>
class Store
{
  public:
    Store(std::shared_ptr<boost::asio::io_context> io_context,
          std::shared_ptr<T> initial_state,
          const std::vector<std::shared_ptr<Updater<T>>>& updaters,
          const std::vector<std::shared_ptr<Flow<T>>>& flows);
    Store() = delete;

    void dispatch(std::shared_ptr<Event> event);

    void run();

    void run_next_event();

  private:
    std::shared_ptr<boost::asio::io_context> io_context;
    std::shared_ptr<T> state;

    std::queue<std::shared_ptr<Event>> events;
    const std::vector<std::shared_ptr<Updater<T>>> updaters;
    const std::vector<std::shared_ptr<Flow<T>>> flows;
};

} // namespace pizone

#endif // PIZONE_STORE_HPP
