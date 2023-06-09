#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "ToStringSpecializations.h"
#include "DefaultEquality.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DefaultEqualityTests)
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

		TEST_METHOD(DefaultTemplate)
		{
			const Foo a(10);
			const Foo b(20);
			const Foo c(10);
			DefaultEquality<Foo> eq;

			Assert::IsFalse(eq(a, b));
			Assert::IsFalse(eq(b, c));
			Assert::IsTrue(eq(a, c));
		}

		TEST_METHOD(CharPointerEquality)
		{
			const char* a = "Hello";
			const char* b = "Goodbye";
			char c[6];
			strncpy_s(c, a, strlen(a));

			{
				DefaultEquality<char*> eq;
				Assert::IsFalse(eq(a, b));
				Assert::IsFalse(eq(b, c));
				Assert::IsTrue(eq(a, c));
			}

			{
				DefaultEquality<const char*> eq;
				Assert::IsFalse(eq(a, b));
				Assert::IsFalse(eq(b, c));
				Assert::IsTrue(eq(a, c));
			}

			{
				DefaultEquality<char* const> eq;
				Assert::IsFalse(eq(a, b));
				Assert::IsFalse(eq(b, c));
				Assert::IsTrue(eq(a, c));
			}

			{
				DefaultEquality<const char* const> eq;
				Assert::IsFalse(eq(a, b));
				Assert::IsFalse(eq(b, c));
				Assert::IsTrue(eq(a, c));
			}
		}
	private:
		inline static _CrtMemState _startMemState;
	};
}