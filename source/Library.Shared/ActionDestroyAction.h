#pragma once
#include "Action.h"
//#include "Vector.h"

namespace FIEAGameEngine
{
	class ActionDestroyAction final : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action);
	private:
		/// <summary>
		/// Class name 
		/// </summary>
		std::string _className;
		/// <summary>
		/// Instance NAme
		/// </summary>
		std::string _instanceName;
		/// <summary>
		/// Scope of Target
		/// </summary>
		Scope* _targetScope;
	public:
		/// <summary>
		/// Default Constructor 
		/// </summary>
		ActionDestroyAction();
		/// <summary>
		/// Defaulted copy constructor
		/// </summary>
		ActionDestroyAction(const ActionDestroyAction& other) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		ActionDestroyAction(ActionDestroyAction&& other) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		ActionDestroyAction& operator=(const ActionDestroyAction& other) = default;
		/// <summary>
		/// Defaulted move assignment operator
		/// </summary>
		ActionDestroyAction& operator=(ActionDestroyAction&& other) noexcept = default;
		/// <summary>
		/// Defaulted virtual destructor
		/// </summary>
		~ActionDestroyAction() = default;
		/// <summary>
		/// Updates actions with the Game time
		/// </summary>
		/// <param name="time">reference to game time variable</param>
		void Update(const GameTime& time) override;
		/// <summary>
		/// Vector of the signatures of members of the class
		/// </summary>
		static const Vector<Signature> Signatures();
		/// <summary>
		/// Get the CLass name
		/// </summary>
		const std::string& GetClassName() const;
		/// <summary>
		/// Get the instance name
		/// </summary>
		const std::string& GetInstanceName() const;
		/// <summary>
		/// Set Class Name
		/// </summary>
		void SetClassName(const std::string& className);
		/// <summary>
		/// Set Instance Name
		/// </summary>
		void SetInstanceName(const std::string& instanceName);
	};
	ConcreteFactory(ActionDestroyAction, RTTI);
}
