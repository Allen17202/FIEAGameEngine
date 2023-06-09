#include "pch.h"
#include "ActionListWhile.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionListWhile);

	ActionListWhile::ActionListWhile():
		ActionList(ActionListWhile::TypeIdClass())
	{
	}
	void ActionListWhile::Update(const GameTime& time)
	{
		if (_condition == 1)
		{
			for (std::size_t i = 0; i < Find("Actions")->Size(); ++i)
			{
				GetActionAtIndex(i).Update(time);
			}
		}
	}
	const Vector<Signature> ActionListWhile::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(ActionListWhile, _actionName)},
			{ "Condition", Datum::DatumTypes::Integer, 1, offsetof(ActionListWhile, _condition) },
			{ "Actions", Datum::DatumTypes::Table, 0, 0 },
		};
	}
	bool ActionListWhile::GetCondition() const
	{
		return _condition == 1;
	}
	void ActionListWhile::SetCondition(bool val)
	{
		if (val)
		{
			_condition = 1;
		}
		else
		{
			_condition = 0;
		}
	}
}
