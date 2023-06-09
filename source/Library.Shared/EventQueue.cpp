#include "pch.h"
#include "EventQueue.h"
#include <algorithm>
namespace FIEAGameEngine
{
	void EventQueue::Enqueue(std::shared_ptr<EventPublisher> publisher, GameTime time, std::chrono::milliseconds delay)
	{
		std::pair<std::shared_ptr<EventPublisher>, TimeEvents> eventPair = std::make_pair(publisher, TimeEvents{time.CurrentTime(), delay});
		_listEvents.PushBack(eventPair);
	}

	void EventQueue::CallDeliver(std::shared_ptr<EventPublisher> publish)
	{
		publish->Deliver();
	}

	void EventQueue::Update(GameTime time)
	{
		auto condition = [&time, this](std::pair<std::shared_ptr<EventPublisher>, TimeEvents> eventPair) 
		{
			return isExpired(time.CurrentTime(), eventPair.second);
		};
		condition;

		auto iterator = std::partition(_listEvents.begin(),_listEvents.end(), condition);

		for (auto it = _listEvents.begin(); it != iterator; ++it)
		{
			CallDeliver((*it).first);
		}
		_listEvents.Remove(_listEvents.begin(), iterator);
	}

	void EventQueue::Clear()
	{
		_listEvents.Clear();
	}

	bool EventQueue::isEmpty()
	{
		return _listEvents.IsEmpty();
	}

	std::size_t EventQueue::Size() const
	{
		return _listEvents.Size();
	}

	bool EventQueue::isExpired(std::chrono::high_resolution_clock::time_point curTime, const TimeEvents& time) const
	{
		return ((curTime - time.TimeEnqueued) >= time.Delay);
	}
}

