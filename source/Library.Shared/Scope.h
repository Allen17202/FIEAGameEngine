#pragma once
#include "HashMap.h"
#include "Datum.h"
#include "Vector.h"
#include "RTTI.h"

#ifdef _WIN32
#include <gsl/gsl>
#else defined(__linux__)
#include <gsl/gsl>
#endif

#include "Factory.h"
namespace FIEAGameEngine
{
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI);
	public:
		/// <summary>
		/// Constructor to take the initial capacity of the scope: just in case size of table is known in advance
		/// </summary>
		/// <param name="_capacity"> initial capacity of the Scope</param>
		Scope(std::size_t capacity = 11);

		/// <summary>
		/// Copy Constructor: creates another scope based on the given scope, does not pass the parent reference
		/// </summary>
		/// <param name="other"></param>
		Scope(const Scope& other);

		/// <summary>
		/// Copy Assignment Operator: set the scopes equal to one another
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Scope& operator=(const Scope& other); // could use Append do not use AppendScope help mee

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other"></param>
		Scope(Scope&& other) noexcept;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Scope& operator=(Scope&& other) noexcept;

		/// <summary>
		/// Destructor
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		virtual ~Scope(); // 

		//[[nodiscard]] virtual gls::owner(Scope*) Clone() const;

		/// <summary>
		/// Equality Operator for Scope: indicates whether two scope objects have matching contents
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(const Scope& other) const;
		/// <summary>
		/// Inequality Operator for Scope
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(const Scope& rhs) const;
		/// <summary>
		/// Bracket Operator: Wraps Append
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns></returns>
		Datum& operator[](const std::string& valueName);

		/// <summary>
		/// Bracket Operator: returns reference to datum at index specified
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		Datum& operator[](std::size_t valueIndex);

		/// <summary>
		/// Bracket Operator: Wraps Append
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns></returns>
		const Datum& operator[](const std::string& valueName)const;

		/// <summary>
		/// Bracket Operator: returns reference to datum at index specified
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		const Datum& operator[](std::size_t valueIndex) const;

		/// <summary>
		/// Ownership is being transferred
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		//[[nodiscard]] virtual gsl::owner<Scope*> Clone() const;
		
#ifdef _WIN32
		/// <summary>
		/// Ownership is being transferred
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		[[nodiscard]] virtual gsl::owner<Scope*> Clone() const;
#elif defined(__linux__)

		/// <summary>
		/// Ownership is being transferred
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		[[nodiscard]] virtual gsl::owner<std::unique_ptr<Scope>> Scope::Clone() const;
#endif
		


		/// <summary>
		/// return address of Datum associated with name in Scope, nullptr otherwwise
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns></returns>
		Datum* Find(const std::string& valueName);

		/// <summary>
		/// return address of Datum associated with name in Scope, nullptr otherwwise
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns></returns>
		const Datum* Find(const std::string& valueName) const;

		/// <summary>
		/// Looks for Datum assocaited with most closely nested Datum associated
		/// with given name in this scpe or its ancestors
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns>Address of Datum</returns>
		Datum* Search(const std::string& valueName);

		/// <summary>
		/// Looks for Datum assocaited with most closely nested Datum associated
		/// with given name in this scpe or its ancestors
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns>Address of Datum</returns>
		const Datum* Search(const std::string& valueName) const;


		/// <summary>
		/// Looks for Datum assocaited with most closely nested Datum associated
		/// with given name in this scpe or its ancestors
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns>Address of Datum</returns>
		Datum* Search(const std::string& valueName, Scope*& foundScope);

		/// <summary>
		/// Looks for Datum assocaited with most closely nested Datum associated
		/// with given name in this scpe or its ancestors
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns>Address of Datum</returns>
		const Datum* Search(const std::string& valueName,const Scope*& foundScope) const;


		/// <summary>
		/// Values are appended and reference returned
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns>Reference to Datum with one, if not found then creates one</returns>
		Datum& Append(const std::string& valueName);
		
		/// <summary>
		/// Retruns referenceto nested scope with name within this scope
		/// If not found then makes a new one
		/// </summary>
		/// <param name="valueName"></param>
		/// <returns></returns>
		Scope& AppendScope(const std::string& valueName);
		
		/// <summary>
		/// Equals for RTTI in Scope
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool Equals(const RTTI* other) const;

		/// <summary>
		/// Adopts a Scope
		/// Takes a reference to Scope which is the child to adopt
		/// </summary>
		/// <param name="child"></param>
		/// <param name="valueName"></param>
		void Adopt(Scope& child, const std::string& valueName);
	
		/// <summary>
		/// Orphans a scope
		/// </summary>
		/// <param name="child"></param>
		void Orphan(Scope& child);
		
		/// <summary>
		/// Returns address of the current scope
		/// </summary>
		/// <returns></returns>
		Scope* GetParent() const;

		/// <summary>
		/// Deletes all memory associated with this object
		/// </summary>
		virtual void Clear();
	
		/// <summary>
		/// Gets size of the scopes order vector
		/// </summary>
		std::size_t Size() const;

		/// <summary>
		/// Searches for scope
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		std::pair<Datum*, std::size_t> FindContainedScope(const Scope& other) const;
	private:
		bool IsAncestorOf(const Scope& scope) const;
		bool IsDescendentOf(const Scope& scope) const;
		Datum& Append(const std::string& valueName, bool& wasAppended);

	protected:
		Scope* _parent{ nullptr };
		HashMap<std::string, Datum> _map;
		Vector<HashMap<std::string, Datum>::pair_type*> _orderVector;
	};
	ConcreteFactory(Scope, RTTI);
}

