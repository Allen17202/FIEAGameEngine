#include "pch.h"
#include "ActionCreateAction.h"
#include "ActionList.h"
#include "GameObject.h"
namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionCreateAction);

	ActionCreateAction::ActionCreateAction():
		Action(ActionCreateAction::TypeIdClass())
	{
	}


	void ActionCreateAction::Update(const GameTime&)
	{
		Scope* scopeParent = GetParent();
		assert(scopeParent != nullptr);
		assert(scopeParent->As<FIEAGameEngine::ActionList>() != nullptr || scopeParent->As<FIEAGameEngine::GameObject>() != nullptr);

		assert(_className.empty() == false);
		assert(_instanceName.empty() == false);
		RTTI* r = Factory<RTTI>::Create(_className);
		Action* action = r->As<Action>();
		assert(action != nullptr);
		action->SetName(_instanceName);
		scopeParent->Adopt(*action, "Actions");
	}

	const Vector<Signature> ActionCreateAction::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(ActionCreateAction, _actionName)},
			{ "ClassName", Datum::DatumTypes::String, 1, offsetof(ActionCreateAction, _className) },
			{ "InstanceName", Datum::DatumTypes::String, 1, offsetof(ActionCreateAction, _instanceName) },
			{ "Actions", Datum::DatumTypes::Table, 1, 0 },
		};
	}
	
	const std::string& ActionCreateAction::GetClassName() const
	{
		return _className;
	}
	const std::string& ActionCreateAction::GetInstanceName() const
	{
		return _instanceName;
	}

	void ActionCreateAction::SetClassName(const std::string& className)
	{
		_className = className;
	}

	void ActionCreateAction::SetInstanceName(const std::string& instanceName)
	{
		_instanceName = instanceName;
	}
}