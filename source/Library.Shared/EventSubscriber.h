#pragma once



namespace FIEAGameEngine
{
	/// <summary>
	/// Forward declaraction of Event Publisher
	/// </summary>
	class EventPublisher;

	class EventSubscriber
	{
	public:
		/// <summary>
		/// Defaulted Constructor
		/// </summary>
		EventSubscriber() = default;
		/// <summary>
		/// Defaulted copy constructor
		/// </summary>
		EventSubscriber(const EventSubscriber&) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		EventSubscriber(EventSubscriber&&) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		EventSubscriber& operator=(const EventSubscriber&) = default;
		/// <summary>
		/// Defaulted Move Assignment Operator
		/// </summary>
		EventSubscriber& operator=(EventSubscriber&&) noexcept = default;
		/// <summary>
		/// Defaulted Virtual Destructor
		/// </summary>
		virtual ~EventSubscriber() = default;
		/// <summary>
		/// Pure virtual method that notifies the subscribers about an event
		/// </summary>
		virtual void Notify(const EventPublisher& eventPublisher) = 0;
	};
}
