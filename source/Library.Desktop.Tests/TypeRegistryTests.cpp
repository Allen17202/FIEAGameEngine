#include "pch.h"
#include "CppUnitTest.h"
#include "TypeRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;
using namespace FIEAGameEngine;
namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<FIEAGameEngine::Vector<FIEAGameEngine::Signature>>(const FIEAGameEngine::Vector<FIEAGameEngine::Signature>& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<FIEAGameEngine::Signature>(const FIEAGameEngine::Signature& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<FIEAGameEngine::Datum::DatumTypes>(const FIEAGameEngine::Datum::DatumTypes& t)
	{
		RETURN_WIDE_STRING(&t);
	}
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(TypeRegistryTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(SignatureEquality)
		{
			FIEAGameEngine::Signature signature = FIEAGameEngine::Signature("Data", FIEAGameEngine::Datum::DatumTypes::Integer, 1, 0);
			FIEAGameEngine::Signature signatureTwo = signature;
			Assert::AreEqual(signature._name, signatureTwo._name);
			Assert::AreEqual(signature._type, signatureTwo._type);
			Assert::AreEqual(signature._offset, signatureTwo._offset);
			Assert::AreEqual(signature._size, signatureTwo._size);

			signatureTwo = FIEAGameEngine::Signature("Goober", FIEAGameEngine::Datum::DatumTypes::String, 1, 8);
			Assert::AreNotEqual(signature._name, signatureTwo._name);
			Assert::AreNotEqual(signature._type, signatureTwo._type);
			Assert::AreNotEqual(signature._offset, signatureTwo._offset);
			Assert::AreEqual(signature._size, signatureTwo._size);
		}

		TEST_METHOD(Instances)
		{
			TypeRegistry::CreateInstance();
			Assert::AreEqual(TypeRegistry::Size(), size_t(0));
			Assert::ExpectException<std::runtime_error>([] {TypeRegistry::CreateInstance(); });
			TypeRegistry::Clear();
			TypeRegistry::CreateInstance();
			TypeRegistry::Clear();

		}

		TEST_METHOD(GetSigs)
		{
			FIEAGameEngine::TypeRegistry::CreateInstance();
			Vector<Signature> sigs;
			sigs.PushBack(Signature(Signature("Data", FIEAGameEngine::Datum::DatumTypes::Integer, 1, 0)));
			sigs.PushBack(Signature(Signature("Goober", FIEAGameEngine::Datum::DatumTypes::String, 1, 8)));
			TypeRegistry::InsertType(0, sigs);
			Assert::AreEqual(TypeRegistry::Size(), size_t(1));
			TypeRegistry::Clear();
		}





	private:
		inline static _CrtMemState _startMemState;
	};
}