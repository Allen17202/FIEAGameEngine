#pragma once
#include "Scope.h"
#include "Signature.h"
#include "TypeRegistry.h"
#include "Vector.h"
namespace FIEAGameEngine
{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

	protected:
		/// <summary>
		/// Deleted Default Constructor
		/// </summary>
		Attributed() = delete;
		/// <summary>
		/// Constructor to take a RTTI Id Type
		/// </summary>
		/// <param name="id"> id to be used Populated by Attribute</param>
		Attributed(RTTI::IdType id);
		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other"> object to be copied into this </param>
		Attributed(const Attributed& other);
		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other"> other is the object to be moved</param>
		/// <returns> this containing the contents of other</returns>
		Attributed(Attributed&& other) noexcept;
	public:
		/// <summary>
		/// Assignment Operator: leverages Scopes assignment operator
		/// </summary>
		/// <param name="other"> object to be copied </param>
		/// <returns>this following the copy assignment</returns>
		Attributed& operator=(const Attributed& other);
		/// <summary>
		/// Move Assignment Operator: leverages Scopes move assignment
		/// </summary>
		/// <param name="other"> object to be copied into this</param>
		/// <returns> this </returns>
		Attributed& operator=(Attributed&& other) noexcept;
		/// <summary>
		/// Defaulted Destructor
		/// </summary>
		virtual ~Attributed() = default;

		/// <summary>
		/// IsAttribute: checks whether the string is an attribute
		/// </summary>
		/// <param name="name">name of the object to be found</param>
		/// <returns> whether the name is an attribute</returns>
		bool IsAttribute(const std::string& name) const;
		/// <summary>
		/// Checks whether the string is an prescribed attribute
		/// </summary>
		/// <param name="name">name of the object to be found</param>
		/// <returns> whether the name is an attribute</returns>
		bool IsPrescribedAttribute(const std::string& name) const;
		/// <summary>
		/// Checks whether the string is an auxiliary attribute
		/// </summary>
		/// <param name="name">name of the object to be found</param>
		/// <returns> whether the name is an attribute</returns>
		bool IsAuxiliaryAttribute(const std::string& name) const;
		/// <summary>
		/// Leverages Scopes Append, checks whether the name is a prescibed attribute before appending 
		/// </summary>
		/// <param name="name">name of the object to ne appended</param>
		/// <returns>reference to a Datum</returns>
		Datum& AppendAuxiliaryAttribute(const std::string& name);

		/// <summary>
		/// Getter to the Attributes
		/// </summary>
		/// <returns> order vector</returns>
		const Vector<std::pair<const std::string, Datum>*>& Attributes() const;

		/// <summary>
		/// Getter for Prescribed Attributes
		/// </summary>
		/// <returns>Pairs of string Datums that are Prescribed Attributes</returns>
		Vector<std::pair<const std::string, Datum>*> PrescribedAttributes() const;
		/// <summary>
		/// Getter for Auxiliary Attributes
		/// </summary>
		/// <returns>Pairs of string Datums that are Auxiliary Attributes</returns>
		Vector<std::pair<const std::string, Datum>*> AuxiliaryAttributes() const;
		/// <summary>
		/// USes Datums Append and SetStorage to populate datum with signatures
		/// </summary>
		/// <param name="id"> id used to populate signature</param>
		void Populate(RTTI::IdType id);

		//virtual gsl::owner<Attributed*> Clone() const override = 0;
	private:
		/// <summary>
		/// Does similar work as Populate by populating datum with Signatures
		/// </summary>
		/// <param name="id">id used to get signatures of type</param>
		void UpdateExternalStorage(RTTI::IdType id);
	};
}