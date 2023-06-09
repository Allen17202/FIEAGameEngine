#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "ToStringSpecializations.h"
#include "Factory.h"
#include <crtdbg.h>
//#include "FooFactory.h"
//#include "AttributedFoo.h"
//#include "Scope.h"
//#include "TypeRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;
using namespace std;
using namespace std::string_literals;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(FactoryTests)
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

		TEST_METHOD(FooFactory)
		{
			RTTI* r = Factory<RTTI>::Create("Foo"s);
			Assert::IsNull(r);
			auto located = Factory<RTTI>::Find("Foo"s);
			Assert::IsTrue(located == nullptr);
			Assert::AreEqual(Factory<RTTI>::Size(), size_t(0));
			Factory<RTTI>::Add(std::make_shared<FIEAGameEngine::FooFactory>());
			r = Factory<RTTI>::Create("Foo"s);
			located = Factory<RTTI>::Find("Foo"s);
			Assert::IsFalse(located == nullptr);
			Assert::ExpectException<std::runtime_error>([]() {Factory<RTTI>::Add(std::make_shared<FIEAGameEngine::FooFactory>()); });
			Assert::AreEqual(Factory<RTTI>::Size(), size_t(1));
			Assert::IsNotNull(r);
			Foo* f = r->As<Foo>();
			Assert::IsNotNull(f);
			Factory<RTTI>::Clear();
			Assert::AreEqual(Factory<RTTI>::Size(), size_t(0));
			delete r;
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}