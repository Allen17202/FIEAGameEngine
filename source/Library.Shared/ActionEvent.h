#pragma once
#include "Factory.h"
#include "Action.h"

namespace FIEAGameEngine
{
	class ActionEvent final : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action);

	private:
		/// <summary>
		/// SubType of Event to Generate
		/// </summary>
		std::string _subType;
		/// <summary>
		/// Delay asscoiated with event
		/// </summary>
		std::int32_t _delay;
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionEvent();
		/// <summary>
		/// Defaulted Copy Constructor
		/// </summary>
		ActionEvent(const ActionEvent& other) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		ActionEvent(ActionEvent&& other) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		ActionEvent& operator=(const ActionEvent& other) = default;
		/// <summary>
		/// Defaulted Move Assignment Operator
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		ActionEvent& operator=(ActionEvent&& other) noexcept = default;
		/// <summary>
		/// Defaulted Destructor
		/// </summary>
		~ActionEvent() = default;

		const std::string& GetSubtype() const;
		void SetSubtype(std::string subType);
		std::int32_t GetDelay() const;
		void SetDelay(std::int32_t delay);

		/// <summary>
		/// Pure Virtual Update Method 
		/// </summary>
		/// <param name="time">reference to Game Time variable</param>
		/// NOTDONEEEEE
		void Update(const GameTime& time);

		
		/// <summary>
		/// Signatures of the members of the class
		/// </summary>
		/// <returns>vector of signatures</returns>
		static const Vector<Signature> Signatures();
	};
	ConcreteFactory(ActionEvent, Scope);
}

