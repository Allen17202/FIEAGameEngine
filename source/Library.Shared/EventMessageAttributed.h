#pragma once
#include "Attributed.h"
#include "GameState.h"
#include "TypeRegistry.h" //might not be needed


namespace FIEAGameEngine
{
	
	class EventMessageAttributed : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed);
	private:
		std::string _subType;
		GameState* _gameState;
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		EventMessageAttributed();
		/// <summary>
		/// Default copy constructor
		/// </summary>
		EventMessageAttributed(const EventMessageAttributed&) = default;
		/// <summary>
		/// Default Move Constructor
		/// </summary>
		EventMessageAttributed(EventMessageAttributed&&) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment operator
		/// </summary>
		EventMessageAttributed& operator=(const EventMessageAttributed&) = default;
		/// <summary>
		/// Defaulted Move Asssignment Operator
		/// </summary>
		EventMessageAttributed& operator=(EventMessageAttributed&&) noexcept = default;
		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~EventMessageAttributed() = default;
		/// <summary>
		/// Sets Subtype for the event message attribute
		/// </summary>
		void SetSubtype(const std::string& subType);
		/// <summary>
		/// Gets the subtype of the event message attributed
		/// </summary>
		/// <returns></returns>
		const std::string& GetSubtype() const;
		/// <summary>
		/// Get the Game State
		/// </summary>
		GameState* GetGameState() const;
		/// <summary>
		/// Sets the game state
		/// </summary>
		void SetGameState(GameState& gameState);
		/// <summary>
		/// Vectors of Prescribed Attributes
		/// </summary>
		static const Vector<Signature> Signatures();
	};
}
