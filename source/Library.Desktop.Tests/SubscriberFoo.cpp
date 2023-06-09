#include "pch.h"
#include "SubscriberFoo.h"
#include "Foo.h"
#include "Event.h"

namespace FIEAGameEngine
{
	SubscriberFoo::SubscriberFoo(std::int32_t data):
		_data(data)
	{
	}

	void SubscriberFoo::Notify(const EventPublisher& publisher)
	{
		const Event<Foo>* event = publisher.As<Event<Foo>>();
		if (event != nullptr)
		{
			_data = event->Message().Data();
		}
		_notified = true;
	}
}
