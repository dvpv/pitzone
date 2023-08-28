#include <pizone/provider/Provider.hpp>

namespace pizone
{

template<typename ContentType>
void
Provider<ContentType>::addConsumer(const Consumer<ContentType>& consumer)
{
    callbacks.push_back(std::bind(&Consumer<ContentType>::consume, &consumer, std::placeholders::_1));
}

template<typename ContentType>
void
Provider<ContentType>::notifyConsumers(const ContentType& content)
{
    for (const ContentCallback<ContentType>& callback : callbacks)
    {
        callback(content);
    }
}

} // namespace pizone
