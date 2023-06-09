#pragma once

#include "CppUnitTest.h"
#include "Foo.h"
#include "SList.h"
#include "Vector.h"
#include "Datum.h"
#include "RTTI.h"
#include <stdexcept>
using namespace std::string_literals;
using namespace FIEAGameEngine;
using namespace std;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	
	template<>
	inline std::wstring ToString<FIEAGameEngine::Foo>(const FIEAGameEngine::Foo& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString<FIEAGameEngine::Foo>(const FIEAGameEngine::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FIEAGameEngine::Foo>(FIEAGameEngine::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}


	/*template<>
	std::wstring ToString<Datum::DatumTypes>(const Datum::DatumTypes& d)
	{
		try
		{
			switch (d)
			{
			case Datum::DatumTypes::Unknown:
				return L"Unknown"s;
				break;
			case Datum::DatumTypes::Integer:
				return L"Integer"s;
				break;
			case Datum::DatumTypes::Float:
				return L"Float"s;
				break;
			case Datum::DatumTypes::String:
				return L"String"s;
				break;
			case Datum::DatumTypes::Vector:
				return L"Vector"s;
				break;
			case Datum::DatumTypes::Matrix:
				return L"Matrix"s;
				break;
			case Datum::DatumTypes::Pointer:
				return L"Pointer"s;
				break;
			case Datum::DatumTypes::Table:
				return L"Table"s;
				break;
			default:
				return L"error"s;
				break;
			}
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}

	template<>
	std::wstring ToString<Datum>(const Datum& d)
	{
		try
		{
			return ToString(d.Type());
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}

	template<>
	std::wstring ToString<Datum>(Datum* d)
	{
		try
		{
			return ToString((*d).Type());
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}*/

	/*template<>
	inline std::wstring ToString<Datum>(const Datum& t)
	{
		try
		{
			return ToString(t.Type());
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}

	template<>
	inline std::wstring ToString<Datum>(const Datum* t)
	{
		try
		{
			return ToString((*t).Type());
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}*/



	/*template<>
	inline std::wstring ToString < HashMap<int, Foo>::Iterator(const HashMap<int, Foo>::Iterator* t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString < HashMap<int, Foo>::Iterator(HashMap<int, Foo>::Iterator* t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::Iterator(const HashMap<int, Foo>::Iterator& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString < HashMap<int, Foo>::ConstIterator(const HashMap<int, Foo>::Iterator* t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString < HashMap<int, Foo>::ConstIterator(HashMap<int, Foo>::Iterator* t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString < HashMap<int, Foo>::ConstIterator(const HashMap<int, Foo>::Iterator& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}
*/













	template<>
	inline std::wstring ToString<SList<Foo>::Iterator>(const SList<Foo>::Iterator& t)
	{
		std::wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	inline std::wstring ToString<SList<Foo>::ConstIterator>(const SList<Foo>::ConstIterator& t)
	{
		std::wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	inline std::wstring ToString<Vector<Foo>::Iterator>(const Vector<Foo>::Iterator& t)
	{
		std::wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	inline std::wstring ToString<Vector<Foo>::ConstIterator>(const Vector<Foo>::ConstIterator& t)
	{
		std::wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

}
