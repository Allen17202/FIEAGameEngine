#pragma once
#include "Reaction.h"
#include "Factory.h"


namespace FIEAGameEngine
{
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		ReactionAttributed(const std::string& nameSubtype = "");
		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		ReactionAttributed(const ReactionAttributed& other) = default;
		/// <summary>
		/// Default Move Constructor
		/// </summary>
		ReactionAttributed(ReactionAttributed&& other) noexcept = default;
		/// <summary>
		/// Default copy assignment operator
		/// </summary>
		ReactionAttributed& operator=(const ReactionAttributed& other) = default;
		/// <summary>
		/// Default Move assignment operator
		/// </summary>
		ReactionAttributed& operator=(ReactionAttributed&& other) noexcept = default;
		/// <summary>
		/// Default Destructor
		/// </summary>
		~ReactionAttributed();


		void Notify(const EventPublisher& publisher) override;
		const std::string& GetSubtype() const;
		static const Vector<Signature> Signatures();
	private:
		/// <summary>
		/// Subtpe of Reaction Attributed
		/// </summary>
		std::string _subType;

	};
	ConcreteFactory(ReactionAttributed, Scope);
}
