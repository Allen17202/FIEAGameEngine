#include "pch.h"
#include "EventMessageAttributed.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(EventMessageAttributed);

	EventMessageAttributed::EventMessageAttributed():
		Attributed(EventMessageAttributed::TypeIdClass())
	{
	}

	void EventMessageAttributed::SetSubtype(const std::string& subType)
	{
		_subType = subType;
	}

	const std::string& EventMessageAttributed::GetSubtype() const
	{
		return _subType;
	}

	GameState* EventMessageAttributed::GetGameState() const
	{
		return _gameState;
	}

	void EventMessageAttributed::SetGameState(GameState& gameState)
	{
		_gameState = &gameState;
	}

	const Vector<Signature> EventMessageAttributed::Signatures()
	{
		return Vector<Signature>
		{
			{"Subtype", Datum::DatumTypes::String, 1, offsetof(EventMessageAttributed, _subType) },
		};
	}
}
