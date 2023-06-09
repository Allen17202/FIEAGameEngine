#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"


namespace FIEAGameEngine
{
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList);
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		Reaction() = default;
		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		Reaction(const Reaction& other) = default;
		/// <summary>
		/// Default Move Constructor
		/// </summary>
		Reaction(Reaction&& other) noexcept= default;
		/// <summary>
		/// Default copy assignment operator
		/// </summary>
		Reaction& operator=(const Reaction& other) = default;
		/// <summary>
		/// Default Move assignment operator
		/// </summary>
		Reaction& operator=(Reaction&& other) noexcept = default;

		virtual void Notify(const EventPublisher& publisher) = 0;
		virtual void Update(GameState&) {};
	protected:
		/// <summary>
		/// Constructor that allows derived classes to pass id 
		/// </summary>
		/// <param name="id"></param>
		explicit Reaction(RTTI::IdType id);

	};
}