#pragma once
#include "Foo.h"
#include "EventSubscriber.h"

namespace FIEAGameEngine
{
	class SubscriberRemove final : public EventSubscriber
	{
	public:
		std::int32_t _data;
		bool _notified{ false };

		SubscriberRemove(std::int32_t data = 0);
		SubscriberRemove(const SubscriberRemove& rhs) = default; // Copy Construcotr
		SubscriberRemove(SubscriberRemove&& rhs) noexcept = default; // Constructor
		SubscriberRemove& operator=(const SubscriberRemove& rhs) = default; // Constructor
		SubscriberRemove& operator=(SubscriberRemove&& rhs) noexcept = default;
		virtual ~SubscriberRemove() = default;

		void Notify(const EventPublisher& publisher) override;
	};

}
