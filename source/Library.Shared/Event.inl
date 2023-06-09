#include "Event.h"

namespace FIEAGameEngine
{
	template <typename Tmessage>
	RTTI_DEFINITIONS(Event<Tmessage>);

	template<typename Tmessage>
	inline Event<Tmessage>::Event(const Tmessage& message):
		EventPublisher(_listSubscribers), _message(message)
	{
	}
	template<typename Tmessage>
	inline Event<Tmessage>::Event(Tmessage&& message):
		EventPublisher(_listSubscribers), _message(std::move(message))
	{
	}
	template<typename Tmessage>
	inline void Event<Tmessage>::Subscribe(EventSubscriber& subscriber)
	{
		if (!_listPendingAdds.Contains(&subscriber))
		{
			_listPendingAdds.PushBack(&subscriber);
		}
	}

	template<typename Tmessage>
	inline void FIEAGameEngine::Event<Tmessage>::Unsubscribe(EventSubscriber& subscriber)
	{
		if (!_listPendingRemovals.Contains(&subscriber))
		{
			_listPendingRemovals.PushBack(&subscriber);
		}
	}
	template<typename Tmessage>
	inline void Event<Tmessage>::UnSubscribeAll()
	{
		_listSubscribers.Clear();
		_listSubscribers.Resize(0); // Check this
	}
	template<typename Tmessage>
	inline void Event<Tmessage>::PendingSubscribersManager()
	{
		for (auto& subscriber : _listPendingAdds)
		{
			_listSubscribers.PushBack(subscriber);
		}

		for (auto& subscriber : _listPendingRemovals)
		{
			_listSubscribers.Remove(subscriber);
		}

		_listPendingAdds.Clear();
		_listPendingAdds.Resize(0);
		_listPendingRemovals.Clear();
		_listPendingRemovals.Resize(0);

	}
	template<typename Tmessage>
	inline const Tmessage& Event<Tmessage>::Message() const
	{
		return _message;
	}
	template<typename Tmessage>
	inline std::string Event<Tmessage>::ToString() const
	{
		return "Event";
	}
	template<typename Tmessage>
	inline bool Event<Tmessage>::Equals(const RTTI* other) const
	{
		const auto event = other->As<Event<Tmessage>>();
		if (event == nullptr)
		{
			return false;
		}
		return _message == event->_message;
	}
}
