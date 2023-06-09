#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "ToStringSpecializations.h"
#include "DefaultEquality.h"
#include "HashFunction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;

namespace FIEAGameEngine
{
	template <>
	struct HashFunction<Foo> 
	{
		size_t operator()(Foo& TKey)
		{
			size_type valueData = TKey.Data();
			const uint8_t* value = reinterpret_cast<const uint8_t*>(&valueData);
			return Hashing(value, sizeof(TKey.Data()));
		}
	};
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(HashFunctionTests)
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

		TEST_METHOD(Int)
		{
			int a(10);
			int b(20);
			int c(10);
			HashFunction<int> eq;

			Assert::AreEqual(eq(a), eq(c));
			Assert::AreNotEqual(eq(a), eq(b));
			Assert::AreNotEqual(eq(c), eq(b));
		}

		TEST_METHOD(Double)
		{
			double a(10.5);
			double b(20.7);
			double c(10.5);
			HashFunction<double> eq;

			Assert::AreEqual(eq(a), eq(c));
			Assert::AreNotEqual(eq(a), eq(b));
			Assert::AreNotEqual(eq(c), eq(b));
		}

		TEST_METHOD(FooTest)
		{
			Foo a(10);
			Foo b(20);
			Foo c(10);
			HashFunction<Foo> eq;

			Assert::AreEqual(eq(a), eq(c));
			Assert::AreNotEqual(eq(a), eq(b));
			Assert::AreNotEqual(eq(c), eq(b));
		}

		TEST_METHOD(CharPointer)
		{
			const char* a = "Hello";
			const char* b = "Goodbye";
			char c[6];
			strncpy_s(c, a, strlen(a));
			HashFunction<char*> eq;

			Assert::AreEqual(eq(a), eq(c));
			Assert::AreNotEqual(eq(a), eq(b));
			Assert::AreNotEqual(eq(c), eq(b));
		}	

		TEST_METHOD(String)
		{
			string a = "Hello";
			string b = "Goodbye";
			string c(a);
			HashFunction<string> eq;

			Assert::AreEqual(eq(a), eq(c));
			Assert::AreNotEqual(eq(a), eq(b));
			Assert::AreNotEqual(eq(c), eq(b));
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}