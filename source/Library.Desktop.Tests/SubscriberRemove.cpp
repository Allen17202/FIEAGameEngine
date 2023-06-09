#include "pch.h"
#include "SubscriberRemove.h"
#include "Foo.h"
#include "Event.h"

namespace FIEAGameEngine
{
	SubscriberRemove::SubscriberRemove(std::int32_t data):
		_data(data)
	{
	}

	void SubscriberRemove::Notify(const EventPublisher& publisher)
	{
		const Event<Foo>* event = publisher.As<Event<Foo>>();
		if (event != nullptr)
		{
			_data = event->Message().Data();
			Event<Foo>::Unsubscribe(*this);
		}
		_notified = true;
	}
}
