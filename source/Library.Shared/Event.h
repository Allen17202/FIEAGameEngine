#pragma once
#include "EventPublisher.h"

namespace FIEAGameEngine
{
	template <typename Tmessage>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher);
	private:
		/// <summary>
		/// Message object
		/// </summary>
		Tmessage _message;
		/// <summary>
		/// Vector list of subscibers
		/// </summary>
		inline static Vector<EventSubscriber*> _listSubscribers;
		/// <summary>
		/// Vector list of pending subscribers to be added to a list
		/// </summary>
		inline static Vector<EventSubscriber*> _listPendingAdds;
		/// <summary>
		/// Pending list of subscribers to be removed from the list
		/// </summary>
		inline static Vector<EventSubscriber*> _listPendingRemovals;
	public:
		/// <summary>
		/// Constructor that accepts a Tmessage object
		/// </summary>
		Event(const Tmessage& message = Tmessage());
		/// <summary>
		/// Constructor that takes a rvalue reference to a Tmessage
		/// </summary>
		/// <param name="message"></param>
		Event(Tmessage&& message);
		/// <summary>
		/// Default copy constructor
		/// </summary>
		Event(const Event&) = default;
		/// <summary>
		/// Default Move Constructor
		/// </summary>
		Event(Event&&) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment operator
		/// </summary>
		Event& operator=(const Event&) = default;
		/// <summary>
		/// Defaulted Move Asssignment Operator
		/// </summary>
		Event& operator=(Event&&) noexcept = default;
		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~Event() = default;
		/// <summary>
		/// Adds a event subscriber object to the pending adds list of subscribers
		/// </summary>
		/// <param name="subscriber">reference to an Event subscriber</param>
		static void Subscribe(EventSubscriber& subscriber);
		/// <summary>
		/// Adds a event subscriber to the list of subscribers that are being removed
		/// </summary>
		/// <param name="subscriber">reference to event subscriber</param>
		static void Unsubscribe(EventSubscriber& subscriber);
		/// <summary>
		/// Removes All subscribers from the list of subscribers
		/// </summary>
		static void UnSubscribeAll();
		/// <summary>
		/// Adds the subscribers that need to be added and removes the ones that need to be removed
		/// </summary>
		static void PendingSubscribersManager();
		/// <summary>
		/// Getter for the message object
		/// </summary>
		/// <returns>Tmessage object</returns>
		const Tmessage& Message() const;
		/// <summary>
		/// ToString override for RTTI
		/// </summary>
		/// <returns></returns>
		virtual std::string ToString() const override;
		/// <summary>
		/// Equals override for RTTI
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		virtual bool Equals(const RTTI* other) const override;
	};
}
#include "Event.inl"
