#include "pch.h"
#include "ReactionAttributed.h"
#include "Event.h"
#include "EventMessageAttributed.h"

namespace FIEAGameEngine
{

	RTTI_DEFINITIONS(ReactionAttributed);

	ReactionAttributed::ReactionAttributed(const std::string& nameSubtype)
		: Reaction(ReactionAttributed::TypeIdClass()), _subType(nameSubtype)
	{
		Event<EventMessageAttributed>::Subscribe(*this);
	}
	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::UnSubscribeAll();
	}
	void ReactionAttributed::Notify(const EventPublisher& publisher)
	{
		const auto event = publisher.As<Event<EventMessageAttributed>>();
		assert(event != nullptr);
		const auto& message = event->Message();

		if (message.GetSubtype() == _subType)
		{
			Scope s;
			auto auxAttribues = message.AuxiliaryAttributes();
			for (auto pairs : auxAttribues)
			{
				Datum& tempDatum = s.Append(pairs->first);
				if (pairs->second.Type() == Datum::DatumTypes::Table)
				{
					for (std::size_t i = 0; i < pairs->second.Size(); ++i)
					{
						Scope* tempScope = pairs->second.GetTable(i).Clone();
						s.Adopt(*tempScope, pairs->first);
					}
				}
				else
				{
					tempDatum = pairs->second;
				}
			}
			GameState* gameState = message.GetGameState();
			gameState->_scopeStack.Push(&s);
		
			ActionList::Update(gameState->GetGameTime());
			gameState->_scopeStack.Pop();

		}
	}
	const std::string& ReactionAttributed::GetSubtype() const
	{
		return _subType;
	}
	const Vector<Signature> ReactionAttributed::Signatures()
	{
		return Vector<Signature>
		{
			{"Subtype", Datum::DatumTypes::String, 1, offsetof(ReactionAttributed, _subType) },
		};
	}
}
