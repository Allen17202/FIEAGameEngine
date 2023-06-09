#pragma once
#include "Action.h"

namespace FIEAGameEngine
{
	class ActionIncrement final : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action);

	private:
		/// <summary>
		/// Strng name of Target
		/// </summary>
		std::string _target;
		/// <summary>
		/// Datum of Target
		/// </summary>
		Datum* _targetDatum{ nullptr };
		/// <summary>
		/// Value Added at each update call
		/// </summary>
		std::int32_t _step{ 1 };
	public:
		/// <summary>
		/// Default Constructor 
		/// </summary>
		ActionIncrement();
		/// <summary>
		/// Defaulted copy constructor
		/// </summary>
		ActionIncrement(const ActionIncrement& other) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		ActionIncrement(ActionIncrement&& other) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		ActionIncrement& operator=(const ActionIncrement& other) = default;
		/// <summary>
		/// Defaulted move assignment operator
		/// </summary>
		ActionIncrement& operator=(ActionIncrement&& other) noexcept = default;
		/// <summary>
		/// Defaulted virtual destructor
		/// </summary>
		~ActionIncrement() = default;
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
		/// Getter for target
		/// </summary>
		const std::string& GetTarget() const;
		/// <summary>
		/// Set Target
		/// </summary>
		/// <param name="target">string name of the target</param>
		void SetTarget(const std::string& target);
		/// <summary>
		/// Get the int 32 step value
		/// </summary>
		std::int32_t GetStep() const;
		/// <summary>
		/// Set the step value
		/// </summary>
		/// <param name="step">value to be incremented</param>
		void SetStep(std::int32_t step);
		
	};
	ConcreteFactory(ActionIncrement, RTTI);
}
