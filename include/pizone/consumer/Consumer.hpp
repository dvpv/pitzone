
#ifndef __PIZONE_CONSUMER_CONSUMER_HPP__
#define __PIZONE_CONSUMER_CONSUMER_HPP__

#include <type_traits>

namespace pizone
{

template<typename ContentType>
class Consumer
{
  public:
    Consumer(const Consumer&) = delete;
    Consumer(Consumer&&) = delete;
    Consumer& operator=(const Consumer&) = delete;
    Consumer& operator=(Consumer&&) = delete;
    virtual ~Consumer() = 0;

    virtual void consume(const ContentType& content) = 0;

  protected:
    Consumer() = default;
};

} // namespace pizone

#endif // __PIZONE_CONSUMER_CONSUMER_HPP__
