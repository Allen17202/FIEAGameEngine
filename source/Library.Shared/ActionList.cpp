#include "pch.h"
#include "ActionList.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionList);

	ActionList::ActionList(RTTI::IdType id):
		Action(id)
	{
	}
	ActionList::ActionList():
		Action(ActionList::TypeIdClass())
	{
	}
	void ActionList::Update(const GameTime& time)
	{

		for (std::size_t i = 0; i < Find("Actions")->Size(); ++i)
		{
			GetActionAtIndex(i).Update(time);
		}
	}
	Datum& ActionList::Actions()
	{
		Datum* actions = Find("Actions");
		assert(actions != nullptr);
		return *actions;
	}
	Action* ActionList::CreateAction(const std::string& className, const std::string& instanceName)
	{
		auto r = Factory<RTTI>::Create(className);
		assert(r != nullptr);
		Action* act = r->As<Action>();
		assert(act != nullptr);
		act->SetName(instanceName);
		Adopt(*act, "Actions");
		return act;
	}
	Action& ActionList::GetActionAtIndex(std::size_t i)
	{
		Datum& actions = Actions();
		Action& action = static_cast<Action&>(actions.GetTable(i));
		return action;
	}
	const Vector<Signature> ActionList::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(ActionList, _actionName)},
			{ "Actions", Datum::DatumTypes::Table, 0, 0}
		};
	}
}