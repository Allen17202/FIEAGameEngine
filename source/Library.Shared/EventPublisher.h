#pragma once
#include "RTTI.h"
#include "EventSubscriber.h"
#include "Vector.h"

namespace FIEAGameEngine
{
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI);
	protected:
		/// <summary>
		/// Constructor that accepts list of Subscribers
		/// </summary>
		/// <param name="listSubscribers">reference to a list of subscribers</param>
		EventPublisher(Vector<EventSubscriber*>& listSubscribers);
	private:
		/// <summary>
		/// Vector List of Subscribers
		/// </summary>
		Vector<EventSubscriber*>* _listSubscribers;
	public:
		/// <summary>
		/// Defaulted  Copy Constructor
		/// </summary>
		EventPublisher(const EventPublisher&) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		EventPublisher(EventPublisher&&) noexcept = default;
		/// <summary>
		/// Defaulted copy assignment operator
		/// </summary>
		EventPublisher& operator=(const EventPublisher&) = default;
		/// <summary>
		/// Defaulted Move Assignment Operator
		/// </summary>
		EventPublisher& operator=(EventPublisher&&) noexcept = default;
		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~EventPublisher() = default;
		/// <summary>
		/// Notifys the subscribers about an event
		/// </summary>
		void Deliver();
		/// <summary>
		/// To String override for RTTI
		/// </summary>
		virtual std::string ToString() const override;
		/// <summary>
		/// Equals override for Event Publiher
		/// </summary>
		virtual bool Equals(const RTTI* other) const override;
	};
}
