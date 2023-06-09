#include "pch.h"
#include "Attributed.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Attributed);

	Attributed::Attributed(RTTI::IdType id)
	{
		(*this)["this"] = this;
		Populate(id);
	}
	Attributed::Attributed(const Attributed& other):
		Scope(other)
	{
		(*this)["this"] = this;
		UpdateExternalStorage(other.TypeIdInstance());
	}
	Attributed::Attributed(Attributed&& other) noexcept:
		Scope(std::move(other))
	{
		(*this)["this"] = this;
		UpdateExternalStorage(other.TypeIdInstance());
	}
	Attributed& Attributed::operator=(const Attributed& other)
	{
		if (&other != this)
		{
			Scope::operator=(other);
			(*this)["this"] = this;
			UpdateExternalStorage(other.TypeIdInstance());
		}
		return *this;
	}
	Attributed& Attributed::operator=(Attributed&& other) noexcept
	{
		if (&other != this)
		{
			Scope::operator=(std::move(other));
			(*this)["this"] = this;
			UpdateExternalStorage(other.TypeIdInstance());
		}
		return *this;
	}
	
	bool Attributed::IsAttribute(const std::string& name) const
	{
		return (Find(name) != nullptr);
	}
	bool Attributed::IsPrescribedAttribute(const std::string& name) const
	{
		bool wasFound = false;
		const Vector<Signature>& sigs = TypeRegistry::GetSigsOfType(TypeIdInstance());
		for (const auto& sig : sigs)
		{
			if (sig._name == name)
			{
				wasFound = true;
			}
		}
		return wasFound;
	}
	bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
	{
		return (IsAttribute(name) && !IsPrescribedAttribute(name));
	}
	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::runtime_error("Can not be a Prescribed Attribute");
		}
		return Append(name);
	}
	const Vector<std::pair<const std::string, Datum>*>& Attributed::Attributes() const
	{
		return _orderVector;
	}
	Vector<std::pair<const std::string, Datum>*> Attributed::PrescribedAttributes() const
	{
		Vector<std::pair<const std::string, Datum>*> listPrescribedAttributes;
		auto numberOfPrescribedAttributes = TypeRegistry::GetSigsOfType(TypeIdInstance()).Size() + 1;
		if (numberOfPrescribedAttributes == Size())
		{
			listPrescribedAttributes = _orderVector;
		}
		else
		{
			listPrescribedAttributes.Reserve(numberOfPrescribedAttributes);
			for (size_t i = 0; i < numberOfPrescribedAttributes; ++i)
			{
				listPrescribedAttributes.PushBack(_orderVector[i]);
			}
		}
		return listPrescribedAttributes;
	}
	Vector<std::pair<const std::string, Datum>*> Attributed::AuxiliaryAttributes() const
	{
		Vector<std::pair<const std::string, Datum>*> listAuxiliaryAttributes;
		auto numberOfAuxiliaryAttributes = TypeRegistry::GetSigsOfType(TypeIdInstance()).Size() + 1;
		if (numberOfAuxiliaryAttributes < Size())
		{
			for (size_t i = numberOfAuxiliaryAttributes; i < _orderVector.Size(); ++i)
			{
				listAuxiliaryAttributes.PushBack(_orderVector[i]);
			}
		}
		return listAuxiliaryAttributes;
	}
	void Attributed::Populate(RTTI::IdType id)
	{
		const Vector<Signature>& sigs = TypeRegistry::GetSigsOfType(id);
		for (const auto& sig : sigs)
		{
			Datum& dat = Append(sig._name);
			dat.SetType(sig._type);
			if (sig._type != Datum::DatumTypes::Table)
			{
				dat.SetStorage(dat.Type(), reinterpret_cast<std::uint8_t*>(this) + sig._offset, sig._size);
			}
			else
			{
				dat.Reserve(sig._size);
			}
		}
	}
	void Attributed::UpdateExternalStorage(RTTI::IdType id)
	{
		const Vector<Signature>& sigs = TypeRegistry::GetSigsOfType(id);
		for (const auto& sig : sigs)
		{
			Datum& dat = Append(sig._name);
			if (sig._type != Datum::DatumTypes::Table)
			{
				Datum::DatumTypes previousDatumType = dat.Type();
				dat.SetStorage(previousDatumType, reinterpret_cast<std::uint8_t*>(this) + sig._offset, sig._size);
			}
		}
	}
}
