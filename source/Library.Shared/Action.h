#pragma once
#include "Attributed.h"
#include "GameTime.h"

namespace FIEAGameEngine
{
	class GameState;
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed);
	protected:
		/// <summary>
		/// Constructor that allows derived classes to pass id up to Attributed
		/// </summary>
		Action(RTTI::IdType id);
		/// <summary>
		/// Data member for the action name
		/// </summary>
		std::string _actionName;
	public:
		/// <summary>
		/// Defaulted Copy Constructor
		/// </summary>
		Action(const Action& other) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		Action(Action&& other) noexcept= default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		Action& operator=(const Action& other) = default;
		/// <summary>
		/// Defaulted Move Assignment Operator
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Action& operator=(Action&& other) noexcept = default;
		/// <summary>
		/// Defaulted Virtual Destructor
		/// </summary>
		virtual ~Action() = default;

		/// <summary>
		/// Pure Virtual Update Method 
		/// </summary>
		/// <param name="time">reference to Game Time variable</param>
		virtual void Update(const GameTime& time) = 0;
		/// <summary>
		/// Gets the name of an action
		/// </summary>
		/// <returns>string reference of the string name of the action</returns>
		const std::string& Name() const noexcept;
		/// <summary>
		/// Sets the name of the action
		/// </summary>
		/// <param name="actionName"> string name of an action</param>
		void SetName(const std::string& actionName) noexcept;
		/// <summary>
		/// Signatures of the members of the class
		/// </summary>
		/// <returns>vector of signatures</returns>
		static const Vector<Signature> Signatures();
	};
}
