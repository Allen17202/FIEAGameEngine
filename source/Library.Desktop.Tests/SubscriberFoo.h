#pragma once
#include "Foo.h"
#include "EventSubscriber.h"

namespace FIEAGameEngine 
{
	class SubscriberFoo final : public EventSubscriber
	{
	public:
		std::int32_t _data;
		bool _notified{ false };
	
		SubscriberFoo(std::int32_t data = 0);
		SubscriberFoo(const SubscriberFoo& rhs) = default; // Copy Construcotr
		SubscriberFoo(SubscriberFoo&& rhs) noexcept = default; // Constructor
		SubscriberFoo& operator=(const SubscriberFoo& rhs) = default; // Constructor
		SubscriberFoo& operator=(SubscriberFoo&& rhs) noexcept = default;
		virtual ~SubscriberFoo() = default;

		void Notify(const EventPublisher& publisher) override;
	};

}