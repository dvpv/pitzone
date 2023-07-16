#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <future>
#include <iostream>
#include <memory>
#include <pizone/pizone.hpp>
#include <vector>

class State
{
  public:
    State(int value)
      : value(value)
    {
    }

    int value;
};

class IncrementEvent : public pizone::Event
{
  public:
    IncrementEvent(int value)
      : value(value)
    {
    }

    int value;
};

void
__updater_method_1(std::shared_ptr<State> state, std::shared_ptr<IncrementEvent> event)
{
    std::cout << __FUNCTION__ << " Incrementing state from " << state->value << " to " << state->value + 1 << std::endl;
    state->value++;
}

int
main()
{
    using namespace pizone;
    std::shared_ptr<boost::asio::io_context> io_context = std::make_shared<boost::asio::io_context>();

    UpdaterCallback<State, IncrementEvent> updater_method_1 = __updater_method_1;

#define WRAP(function, event_type)                                                                                     \
    [&function](std::shared_ptr<State> state, std::shared_ptr<Event> event)                                            \
    { function(state, std::static_pointer_cast<event_type>(event)); }

    std::shared_ptr<Updater<State>> updater =
      std::make_shared<Updater<State>>(std::map<size_t, UpdaterCallback<State, Event>>{
        { typeid(IncrementEvent).hash_code(), WRAP(updater_method_1, IncrementEvent) },
      });

    FlowCallback<State, IncrementEvent> flow_1 = [](std::shared_ptr<State> state, std::shared_ptr<Event> event)
    { std::cout << "Flowing 1" << std::endl; };

    std::shared_ptr<Flow<State>> flow = std::make_shared<Flow<State>>(std::map<size_t, FlowCallback<State, Event>>{
      { typeid(IncrementEvent).hash_code(), WRAP(flow_1, IncrementEvent) },
    });

    Store<State> store(io_context,
                       std::make_shared<State>(0),
                       {
                         updater,
                       },
                       {
                         flow,
                       });

    int times_expired = 0;
    std::shared_ptr<boost::asio::deadline_timer> loop_timer =
      std::make_shared<boost::asio::deadline_timer>(*io_context, boost::posix_time::seconds(1));

    int times_to_loop = 20;

    std::function<void(const boost::system::error_code&)> callback = [](const boost::system::error_code& ec) {};
    callback =
      [&store, &times_to_loop, &times_expired, loop_timer, &callback](const boost::system::error_code& ec) -> void
    {
        std::cout << "1 second has passed" << std::endl;
        store.dispatch(std::make_shared<IncrementEvent>(1));
        times_expired++;
        if (times_expired < times_to_loop)
        {
            loop_timer->expires_from_now(boost::posix_time::seconds(1));
            loop_timer->async_wait(callback);
        }
    };

    callback(boost::system::error_code());

    store.run();
    std::cout << "Bye" << std::endl;

    return 0;
}
