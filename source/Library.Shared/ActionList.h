#pragma once
#include "Action.h"

namespace FIEAGameEngine
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);

	protected:
		/// <summary>
		/// Constructor that allows derived classes to pass id up to Attributed
		/// </summary>
		ActionList(RTTI::IdType id);
		/// <summary>
		/// string of action name
		/// </summary>
		std::string _actionName;
	public:
		/// <summary>
		/// Default Constructor 
		/// </summary>
		ActionList();
		/// <summary>
		/// Defaulted copy constructor
		/// </summary>
		ActionList(const ActionList& other) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		ActionList(ActionList&& other) = default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		ActionList& operator=(const ActionList& other) = default;
		/// <summary>
		/// Defaulted move assignment operator
		/// </summary>
		ActionList& operator=(ActionList&& other) = default;
		/// <summary>
		/// Defaulted virtual destructor
		/// </summary>
		virtual ~ActionList() = default;
		/// <summary>
		/// Updates actions with the Game time
		/// </summary>
		/// <param name="time">reference to game time variable</param>
		virtual void Update(const GameTime& time) override;
		/// <summary>
		/// Getter for the Actions Datum
		/// </summary>
		/// <returns> reference to the Actions datum</returns>
		Datum& Actions();
		/// <summary>
		/// Instantiates a new Action Object and adopts into Actions Datum
		/// </summary>
		/// <param name="className"> class name </param>
		/// <param name="instanceName">instance name</param>
		/// <returns> pointer to the action</returns>
		Action* CreateAction(const std::string& className, const std::string& instanceName);
		/// <summary>
		/// Retrieves an action instance from the actions datum at index i
		/// </summary>
		Action& GetActionAtIndex(std::size_t i = 0);
		/// <summary>
		/// Vector of the signatures of members of the class
		/// </summary>
		static const Vector<Signature> Signatures();
	};
	ConcreteFactory(ActionList, RTTI);
}
