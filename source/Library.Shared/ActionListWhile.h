#pragma once
#include "ActionList.h"


namespace FIEAGameEngine
{
	class ActionListWhile final : public ActionList
	{
		RTTI_DECLARATIONS(ActionListWhile, ActionList);

	private:
		/// <summary>
		/// alue used to decide whether to execute or break
		/// </summary>
		std::int32_t _condition { 0 };
	public:
		/// <summary>
		/// Default Constructor 
		/// </summary>
		ActionListWhile();
		/// <summary>
		/// Defaulted copy constructor
		/// </summary>
		ActionListWhile(const ActionListWhile& other) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		ActionListWhile(ActionListWhile&& other) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		ActionListWhile& operator=(const ActionListWhile& other) = default;
		/// <summary>
		/// Defaulted move assignment operator
		/// </summary>
		ActionListWhile& operator=(ActionListWhile&& other) noexcept = default;
		/// <summary>
		/// Defaulted virtual destructor
		/// </summary>
		~ActionListWhile() = default;
		/// <summary>
		/// Updates actions with the Game time
		/// </summary>
		/// <param name="time">reference to game time variable</param>
		virtual void Update(const GameTime& time) override;
		/// <summary>
		/// Vector of the signatures of members of the class
		/// </summary>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// Get the boolean condition
		/// </summary>
		bool GetCondition() const;
		
		/// <summary>
		/// Set the condition
		/// </summary>
		void SetCondition(bool val);

	};
	ConcreteFactory(ActionListWhile, RTTI);
}
