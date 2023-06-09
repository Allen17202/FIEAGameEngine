#include "pch.h"
#include "EventPublisher.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(EventPublisher);

	EventPublisher::EventPublisher(Vector<EventSubscriber*>& listSubscribers):
		_listSubscribers(&listSubscribers)
	{
	}

	void EventPublisher::Deliver()
	{
		for (auto& eventSubscriber : *_listSubscribers)
		{
			eventSubscriber->Notify(*this);
		}
	}
	std::string EventPublisher::ToString() const
	{
		return "EventPublisher";
	}
	bool EventPublisher::Equals(const RTTI* other) const
	{
		const auto eventPublisher = other->As<EventPublisher>();
		if (eventPublisher == nullptr)
		{
			return false;
		}
		return _listSubscribers == eventPublisher->_listSubscribers;
	}
}
