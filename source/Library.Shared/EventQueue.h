#pragma once
#include "EventPublisher.h"
#include "GameTime.h"
#include "Vector.h"
#include <memory>
namespace FIEAGameEngine
{
	class EventQueue final
	{
	private:
		struct TimeEvents final
		{
			std::chrono::high_resolution_clock::time_point TimeEnqueued;
			std::chrono::milliseconds Delay;
		};
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		EventQueue() = default;
		/// <summary>
		/// Default copy constructor
		/// </summary>
		EventQueue(const EventQueue& other) = default;
		/// <summary>
		/// Default Move Constructor
		/// </summary>
		EventQueue(EventQueue&& other) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment operator
		/// </summary>
		EventQueue& operator=(const EventQueue& other) = default;
		/// <summary>
		/// Defaulted Move Asssignment Operator
		/// </summary>
		EventQueue& operator=(EventQueue&& other) noexcept = default;
		/// <summary>
		/// Virtual Destructor
		/// </summary>
		~EventQueue() = default;
		/// <summary>
		/// Adds an Event to the Event Queue
		/// </summary>
		/// <param name="publisher">shared ptr to a Event Publisher</param>
		/// <param name="time">current time</param>
		/// <param name="delay">delayed time</param>
		void Enqueue(std::shared_ptr<EventPublisher> publisher, GameTime time, std::chrono::milliseconds delay = std::chrono::milliseconds(0));
		/// <summary>
		/// Called during Game::Update, send the events that have expired
		/// </summary>
		/// <param name="time">current time</param>
		void Update(GameTime time);

		/// <summary>
		/// Helper function to call the deliver method from the shared ptr of an event publisher
		/// </summary>
		void CallDeliver(std::shared_ptr<EventPublisher> publish);

		/// <summary>
		/// Clears the Event Queue
		/// </summary>
		void Clear();
		/// <summary>
		/// Bool indicating emptiness of the queue
		/// </summary>
		bool isEmpty();
		/// <summary>
		/// Size of the queue
		/// </summary>
		/// <returns>size of the queue</returns>
		std::size_t Size() const;
		/// <summary>
		/// Bool indicating whether the event time is expired based on current time
		/// </summary>
		bool isExpired(std::chrono::high_resolution_clock::time_point curTime, const TimeEvents& time) const;

	private:
		Vector<std::pair<std::shared_ptr<EventPublisher>, TimeEvents>> _listEvents;
	};
}


