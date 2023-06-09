#include "pch.h"
#include "GameObject.h"
#include "Action.h"
namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(GameObject);

	GameObject::GameObject():
		Attributed(GameObject::TypeIdClass())
	{
	}
	void GameObject::Update(const GameTime& time)
	{
		//assert(_orderVector != nullptr);
		/*for (std::size_t i = 0; i < Find("Children")->Size(); ++i)
		{
			GetChildAtIndex(i).Update(time);
		}*/
	
		for (std::size_t i = 0; i < _orderVector.Size(); ++i)
		{
			GetChildAtIndex(i).Update(time);
			GetActionAtIndex(i).Update(time);
		}
	}
	const Vector<Signature> GameObject::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(GameObject, _name) },
			{ "Position", Datum::DatumTypes::Vector, 1, offsetof(GameObject, _position) },
			{ "Rotation", Datum::DatumTypes::Vector, 1, offsetof(GameObject, _rotation) },
			{ "Scale", Datum::DatumTypes::Vector, 1, offsetof(GameObject, _scale) },
			{ "Children", Datum::DatumTypes::Table, 0, 0 },
			{ "Actions", Datum::DatumTypes::Table, 0, 0 },
		};
	}
	gsl::owner<GameObject*> GameObject::Clone() const
	{
		return new GameObject(*this); 
	}
	bool GameObject::Equals(const RTTI* other) const
	{
		const auto otherGameObject = other->As<GameObject>();
		if (otherGameObject == nullptr)
		{
			return false;
		}

		return _name == otherGameObject->_name &&
			_position == otherGameObject->_position &&
			_rotation == otherGameObject->_rotation &&
			_scale == otherGameObject->_scale &&
			(*this)["Children"] == (*otherGameObject)["Children"];
	}
	std::string GameObject::ToString() const
	{
		return _name;
	}
	Datum& GameObject::GetChildren()
	{
		Datum* kids = Find("Children");
		assert(kids != nullptr);
		return *kids;
	}
	GameObject& GameObject::GetChildAtIndex(std::size_t index)
	{
		Datum& kids = GetChildren();
		GameObject& kid = static_cast<GameObject&>(kids.GetTable(index));
		return kid;
	}

	Datum& GameObject::Actions()
	{
		Datum* actions = Find("Actions");
		assert(actions != nullptr);
		return *actions;
	}

	Action* GameObject::CreateAction(const std::string& className, const std::string& instanceName)
	{
		//Check for  mistakes
		RTTI* r = Factory<Scope>::Create(className);
		assert(r != nullptr);
		Action* act = r->As<Action>();
		assert(act != nullptr);
		act->SetName(instanceName);
		Adopt(*act, "Actions");
		return act;
	}

	Action& GameObject::GetActionAtIndex(std::size_t i)
	{
		Datum& actions = Actions();
		Action& action = static_cast<Action&>(actions.GetTable(i));
		return action;
	}
}
