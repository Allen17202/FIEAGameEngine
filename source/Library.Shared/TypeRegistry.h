#pragma once
#include "RTTI.h"
#include "Signature.h"
#include "HashMap.h"
#include "Vector.h"
namespace FIEAGameEngine
{
	class TypeRegistry final
	{
	public:
		//TypeRegistry(const TypeRegistry& rhs) = delete;
		static void CreateInstance();
		static void InsertType(RTTI::IdType id, const Vector<Signature>& sigs);
		static size_t Size();
		static void Clear();
		static void AddSigOfType(RTTI::IdType id, const Vector<Signature> sigs);
		static const Vector<Signature>& GetSigsOfType(RTTI::IdType id);
	private:
		TypeRegistry() = default;
		using MapType = HashMap<RTTI::IdType, const Vector<Signature>>;
		static MapType* _registry;
	};
}
#include "TypeRegistry.inl"