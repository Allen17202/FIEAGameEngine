#pragma once
#include "Action.h"
#include "Vector.h"

namespace FIEAGameEngine
{
	class ActionCreateAction final : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action);

	private:
		/// <summary>
		/// Class name 
		/// </summary>
		std::string _className;
		/// <summary>
		/// Instance NAme
		/// </summary>
		std::string _instanceName;
	public:
		/// <summary>
		/// Default Constructor 
		/// </summary>
		ActionCreateAction();
		/// <summary>
		/// Defaulted copy constructor
		/// </summary>
		ActionCreateAction(const ActionCreateAction& other) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		ActionCreateAction(ActionCreateAction&& other) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		ActionCreateAction& operator=(const ActionCreateAction& other) = default;
		/// <summary>
		/// Defaulted move assignment operator
		/// </summary>
		ActionCreateAction& operator=(ActionCreateAction&& other) noexcept = default;
		/// <summary>
		/// Defaulted virtual destructor
		/// </summary>
		~ActionCreateAction() = default;
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
		/// Get the class name
		/// </summary>
		const std::string& GetClassName() const;
		/// <summary>
		/// Get the instance Name
		/// </summary>
		const std::string& GetInstanceName() const;
		/// <summary>
		/// Set the class name
		/// </summary>
		void SetClassName(const std::string& className);
		/// <summary>
		/// Set the Instance name
		/// </summary>
		void SetInstanceName(const std::string& instanceName);

	};
	ConcreteFactory(ActionCreateAction, RTTI);
}

