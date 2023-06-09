#include "pch.h"
#include "ActionEvent.h"

namespace FIEAGameEngine {
	RTTI_DEFINITIONS(ActionEvent);
	ActionEvent::ActionEvent():
		Action(ActionEvent::TypeIdClass())
	{
	}
	

	const std::string& ActionEvent::GetSubtype() const
	{
		return _subType;
	}
	void ActionEvent::SetSubtype(std::string subType)
	{
		_subType = std::move(subType);
	}
	std::int32_t ActionEvent::GetDelay() const
	{
		return _delay;
	}
	void ActionEvent::SetDelay(std::int32_t delay)
	{
		_delay = delay;
	}

	const Vector<Signature> ActionEvent::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(ActionEvent, _actionName)},
			{ "Subtype", Datum::DatumTypes::String, 1, offsetof(ActionEvent, _subType) },
			{ "Delay", Datum::DatumTypes::Integer, 1, offsetof(ActionEvent, _delay) },
		};
	}
}
