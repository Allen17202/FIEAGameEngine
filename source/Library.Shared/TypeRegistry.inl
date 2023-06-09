#include "TypeRegistry.h"

namespace FIEAGameEngine
{
	inline void TypeRegistry::InsertType(RTTI::IdType id, const Vector<Signature>& sigs)
	{
		_registry->Insert({ id,sigs });
	}

	inline void FIEAGameEngine::TypeRegistry::Clear()
	{
		delete(_registry);
		_registry = nullptr;
	}

	inline size_t FIEAGameEngine::TypeRegistry::Size()
	{
		return _registry->Size();
	}

	inline void TypeRegistry::CreateInstance()
	{
		if (_registry != nullptr)
		{
			throw std::runtime_error("Cant have more than one type registry");
		}
		_registry = new HashMap<RTTI::IdType, const Vector<Signature>>(27);
	}

	inline void FIEAGameEngine::TypeRegistry::AddSigOfType(RTTI::IdType id, const Vector<Signature> sigs)
	{
		_registry->Insert({id, sigs});
	}

	inline const Vector<Signature>& FIEAGameEngine::TypeRegistry::GetSigsOfType(RTTI::IdType id)
	{
		assert(_registry != nullptr);
		return _registry->At(id);
	}
}