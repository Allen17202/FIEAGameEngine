#include "pch.h"
#include "ActionDestroyAction.h"
#include "ActionList.h"
#include "GameObject.h"
namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionDestroyAction);

	ActionDestroyAction::ActionDestroyAction() :
		Action(ActionDestroyAction::TypeIdClass())
	{
	}


	void ActionDestroyAction::Update(const GameTime&)
	{
		Scope* scopeParent = GetParent();
		assert(scopeParent != nullptr);
		assert((scopeParent->As<FIEAGameEngine::ActionList>() != nullptr) || (scopeParent->As<FIEAGameEngine::GameObject>() != nullptr));

		assert(_className.empty() == false);
		assert(_instanceName.empty() == false);
		Datum* acts = scopeParent->Find("Actions");
		assert(acts != nullptr);

		for (std::size_t i = 0; i < acts->Size(); ++i)
		{
			Scope* s = &acts->GetTable(i);
			Action* act = s->As<FIEAGameEngine::Action>();
			assert(act != nullptr);
			if (act->Name() == _instanceName)
			{
				assert(act->Is(act->TypeIdClass()));
				act->GetParent()->Orphan(*s);
				delete s;
				return;
			}
		}
	}

	const Vector<Signature> ActionDestroyAction::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(ActionDestroyAction, _actionName)},
			{ "ClassName", Datum::DatumTypes::String, 1, offsetof(ActionDestroyAction, _className) },
			{ "InstanceName", Datum::DatumTypes::String, 1, offsetof(ActionDestroyAction, _instanceName) },
			{ "Actions", Datum::DatumTypes::Table, 1, 0 },
		};
	}
	const std::string& ActionDestroyAction::GetClassName() const
	{
		return _className;
	}
	const std::string& ActionDestroyAction::GetInstanceName() const
	{
		return _instanceName;
	}

	void ActionDestroyAction::SetClassName(const std::string& className)
	{
		_className = className;
	}

	void ActionDestroyAction::SetInstanceName(const std::string& instanceName)
	{
		_instanceName = instanceName;
	}
}