#ifndef __PIZONE_PROVIDER_PROVIDER_HPP__
#define __PIZONE_PROVIDER_PROVIDER_HPP__

#include <functional>
#include <list>

#include <pizone/consumer/Consumer.hpp>

namespace pizone
{

template<typename ContentType>
using ContentCallback = std::function<void(ContentType)>;

template<typename ContentType>
class Provider
{
  public:
    Provider(const Provider&) = delete;
    Provider(Provider&&) = delete;
    Provider& operator=(const Provider&) = delete;
    Provider& operator=(Provider&&) = delete;
    virtual ~Provider() = 0;

    void addConsumer(const Consumer<ContentType>& consumer);

  protected:
    Provider() = default;
    void notifyConsumers(const ContentType& content);

    std::list<ContentCallback<ContentType>> callbacks;
};

} // namespace pizone

#endif // __PIZONE_PROVIDER_PROVIDER_HPP__
