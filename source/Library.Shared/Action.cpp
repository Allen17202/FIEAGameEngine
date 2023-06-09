#include "pch.h"
#include "Action.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Action);

	Action::Action(RTTI::IdType id):
		Attributed(id)
	{
	}
	const std::string& Action::Name() const noexcept
	{
		return _actionName;
	}
	void Action::SetName(const std::string& actionName) noexcept
	{
		_actionName = actionName;
	}
	const Vector<Signature> Action::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(Action, _actionName) }
		};
	}
}
