#include "pizone/store/Store.hpp"

namespace pizone
{

template<class T>
Store<T>::Store(std::shared_ptr<boost::asio::io_context> io_context,
                std::shared_ptr<T> initial_state,
                const std::vector<std::shared_ptr<Updater<T>>>& updaters,
                const std::vector<std::shared_ptr<Flow<T>>>& flows)
  : io_context(io_context)
  , state(initial_state)
  , updaters(updaters)
  , flows(flows)
{
}

template<class T>
void
Store<T>::dispatch(std::shared_ptr<Event> event)
{
    events.push(event);
    if (events.size() == 1)
    {
        io_context->post(std::bind(&Store<T>::run_next_event, this));
    }
}

template<class T>
void
Store<T>::run()
{
    io_context->post(std::bind(&Store<T>::run_next_event, this));
    io_context->run();
}

template<class T>
void
Store<T>::run_next_event()
{
    if (events.empty())
    {
        return;
    }

    std::shared_ptr<Event> event = events.front();
    events.pop();

    for (std::shared_ptr<Updater<T>> updater : updaters)
    {
        updater->update(state, event);
    }

    for (std::shared_ptr<Flow<T>> flow : flows)
    {
        flow->handle_event(state, event);
    }

    io_context->post(std::bind(&Store<T>::run_next_event, this));
}

}; // namespace pizone