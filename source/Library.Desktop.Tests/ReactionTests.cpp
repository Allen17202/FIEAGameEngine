#include "pch.h"
#include "CppUnitTest.h"
//#include "Foo.h"
#include "Event.h"
#include "EventQueue.h"
#include "GameTime.h"
//#include "SubscriberFoo.h"
//#include "SubscriberRemove.h"
//#include "ActionListWhile.h"
#include "ReactionAttributed.h"
#include "ToStringSpecializations.h"
//#include "GameObject.h"
#include "EventMessageAttributed.h"
#include <chrono>
#include <crtdbg.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;
using namespace FIEAGameEngine;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	wstring ToString<ReactionAttributed>(ReactionAttributed* t)
	{
		RETURN_WIDE_STRING(t);
	}
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ReactionTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
			TypeRegistry::CreateInstance();
			TypeRegistry::InsertType(ReactionAttributed::TypeIdClass(), ReactionAttributed::Signatures());

#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			TypeRegistry::Clear();
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

		TEST_METHOD(RTTICheck)
		{
			{
				ReactionAttributed reaction("Test");
				Event<EventMessageAttributed>::PendingSubscribersManager();
				RTTI* r = &reaction;
				Assert::IsTrue(r->Is(ReactionAttributed::TypeIdClass()));
				Assert::AreEqual(ReactionAttributed::TypeIdClass(), r->TypeIdInstance());

				ReactionAttributed* temp = r->As<ReactionAttributed>();
				Assert::IsNotNull(temp);
				Assert::AreEqual(&reaction, temp);
			}
		}

		

	private:
		inline static _CrtMemState _startMemState;
	};
}