#include "pch.h"
#include "ActionIncrement.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement);

	ActionIncrement::ActionIncrement():
		Action(ActionIncrement::TypeIdClass())
	{
	}
	void ActionIncrement::Update(const GameTime&)
	{
		if (_target.empty() == false)
		{
			_targetDatum = Search(_target);
			assert(_targetDatum != nullptr);
			_targetDatum->SetInt(_targetDatum->GetInt() + _step);
		}
	}
	const Vector<Signature> ActionIncrement::Signatures()
	{
		//RTTI* rhs;
		//const auto act = rhs->As<ActionIncrement>();
		//auto b = act->As<Action>();
		//auto c = b->As<ActionIncrement>();
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(ActionIncrement, _actionName)},
			{ "Target", Datum::DatumTypes::String, 1, offsetof(ActionIncrement, _target) },
			{ "Step", Datum::DatumTypes::Integer, 1, offsetof(ActionIncrement, _step) },
		};
	}
	
	const std::string& ActionIncrement::GetTarget() const
	{
		return _target;
	}
	void ActionIncrement::SetTarget(const std::string& target)
	{
		_target = target;
	}
	std::int32_t ActionIncrement::GetStep() const
	{
		return _step;
	}
	void ActionIncrement::SetStep(std::int32_t step)
	{
		_step = step;
	}
}
