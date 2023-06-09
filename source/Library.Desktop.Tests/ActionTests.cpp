#include "pch.h"
#include "CppUnitTest.h"
#include "ActionList.h"
#include "ActionIncrement.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionListWhile.h"
#include "ToStringSpecializations.h"
#include "GameObject.h"
#include "JsonParseCoordinator.h"
#include "JsonTableParseHelper.h"
#include <crtdbg.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;
using namespace FIEAGameEngine;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<FIEAGameEngine::ActionList>(const FIEAGameEngine::ActionList& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<FIEAGameEngine::ActionList>(FIEAGameEngine::ActionList* t)
	{
		RETURN_WIDE_STRING(t);
	}

}


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ActionTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);

			TypeRegistry::CreateInstance();
			TypeRegistry::InsertType(GameObject::TypeIdClass(), GameObject::Signatures());
			TypeRegistry::InsertType(Action::TypeIdClass(), Action::Signatures());
			TypeRegistry::InsertType(ActionList::TypeIdClass(), ActionList::Signatures());
			TypeRegistry::InsertType(ActionIncrement::TypeIdClass(), ActionIncrement::Signatures());
			TypeRegistry::InsertType(ActionCreateAction::TypeIdClass(), ActionCreateAction::Signatures());
			TypeRegistry::InsertType(ActionDestroyAction::TypeIdClass(), ActionDestroyAction::Signatures());
			TypeRegistry::InsertType(ActionListWhile::TypeIdClass(), ActionListWhile::Signatures());
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

		TEST_METHOD(ActionIncrement)
		{
		
			Factory<RTTI>::Add(std::make_shared<FIEAGameEngine::ActionIncrementFactory>());
		
			ActionList actions;
			
			const std::string& test = "FamilyGuy";
			Datum& dat = actions.AppendAuxiliaryAttribute(test);
			dat = int32_t(5);

			Assert::AreEqual(ActionIncrement::TypeName(), "ActionIncrement"s);
			auto act = actions.CreateAction(ActionIncrement::TypeName(), "IncrementAction"s);
			Assert::IsNotNull(act);
			FIEAGameEngine::ActionIncrement* actIncrement = act->As<FIEAGameEngine::ActionIncrement>();
			Assert::IsNotNull(actIncrement);
			Assert::AreEqual(std::size_t(1), actions.Find("Actions")->Size());

			actIncrement->SetTarget(test);
			Assert::AreEqual(std::size_t(1), actions.Find("Actions")->Size());
			Assert::AreEqual(test, actIncrement->GetTarget());
			Assert::AreEqual(std::int32_t(5), dat.GetInt());
			Assert::AreEqual(std::int32_t(1), actIncrement->GetStep());

			GameTime t;
			actions.Update(t);
			Assert::AreEqual(std::int32_t(6), dat.GetInt());
			actions.Update(t);
			Assert::AreEqual(std::int32_t(7), dat.GetInt());

			actIncrement->SetStep(int32_t(2));
			Assert::AreEqual(std::int32_t(2), actIncrement->GetStep());

			actions.Update(t);
			Assert::AreEqual(std::int32_t(9), dat.GetInt());

			actions.Update(t);
			Assert::AreEqual(std::int32_t(11), dat.GetInt());

			actions.Update(t);
			Assert::AreEqual(std::int32_t(13), dat.GetInt());
			Factory<RTTI>::Clear();
		}

		TEST_METHOD(ActionCreateAction)
		{

			Factory<RTTI>::Add(std::make_shared<FIEAGameEngine::ActionCreateActionFactory>());
			Factory<RTTI>::Add(std::make_shared<FIEAGameEngine::ActionIncrementFactory>());

			ActionList actions;

			auto act = actions.CreateAction(ActionCreateAction::TypeName(), "Create Action"s);
			Assert::IsNotNull(act);
			auto actCreate = act->As<FIEAGameEngine::ActionCreateAction>();
			Assert::IsNotNull(actCreate);
			Assert::AreEqual(std::size_t(1), actions.Find("Actions")->Size());

			actCreate->SetClassName("ActionIncrement"s);
			actCreate->SetInstanceName("IncrementAction"s);
			Assert::AreEqual(actCreate->GetClassName(), "ActionIncrement"s);
			Assert::AreEqual(actCreate->GetInstanceName(), "IncrementAction"s);
			Assert::AreEqual(std::size_t(1), actions.Find("Actions")->Size());

			GameTime t;
			actions.Update(t);
			Assert::AreEqual(std::size_t(2), actions.Find("Actions")->Size());

			Factory<RTTI>::Clear();
		}
		TEST_METHOD(ActionDestroyAction)
		{
			Factory<RTTI>::Add(std::make_shared<FIEAGameEngine::ActionDestroyActionFactory>());
			Factory<RTTI>::Add(std::make_shared<FIEAGameEngine::ActionIncrementFactory>());

			ActionList actions;

			auto act = actions.CreateAction(ActionDestroyAction::TypeName(), "DestroyAction"s);
			auto actTwo = actions.CreateAction(ActionIncrement::TypeName(), "IncrementAction"s);

			Assert::IsNotNull(act);
			Assert::IsNotNull(actTwo);


			auto actDestroy = act->As<FIEAGameEngine::ActionDestroyAction>();
			Assert::IsNotNull(actDestroy);
			Assert::AreEqual(std::size_t(2), actions.Find("Actions")->Size());

			actDestroy->SetClassName("ActionIncrement"s);
			actDestroy->SetInstanceName("IncrementAction"s);
			Assert::AreEqual(actDestroy->GetClassName(), "ActionIncrement"s);
			Assert::AreEqual(actDestroy->GetInstanceName(), "IncrementAction"s);
	
			auto actIncrement = actTwo->As<FIEAGameEngine::ActionIncrement>();
			Assert::IsNotNull(actIncrement);
			Assert::AreEqual(actDestroy->GetInstanceName(), actIncrement->Name());


			GameTime t;
			actions.Update(t);
			Assert::AreEqual(std::size_t(1), actions.Find("Actions")->Size());
			Factory<RTTI>::Clear();
		}
		TEST_METHOD(ActionListWhile)
		{
			Factory<RTTI>::Add(std::make_shared<FIEAGameEngine::ActionIncrementFactory>());
			FIEAGameEngine::ActionListWhile actions;

			const std::string& test = "FamilyGuy";
			Datum& dat = actions.AppendAuxiliaryAttribute(test);
			dat = int32_t(5);

			auto act = actions.CreateAction(ActionIncrement::TypeName(), "Increment"s);
			Assert::IsNotNull(act);
			FIEAGameEngine::ActionIncrement* actIncrement = act->As<FIEAGameEngine::ActionIncrement>();
			Assert::IsNotNull(actIncrement);
			Assert::AreEqual(std::size_t(1), actions.Find("Actions")->Size());

			actIncrement->SetTarget(test);
			Assert::AreEqual(std::size_t(1), actions.Find("Actions")->Size());
			Assert::AreEqual(test, actIncrement->GetTarget());
			Assert::AreEqual(std::int32_t(5), dat.GetInt());
			Assert::AreEqual(std::int32_t(1), actIncrement->GetStep());

			GameTime t;
			actions.Update(t);
			Assert::AreEqual(std::int32_t(5), dat.GetInt());
			actions.Update(t);
			Assert::AreEqual(std::int32_t(5), dat.GetInt());

			actions.SetCondition(true);
			actions.Update(t);
			Assert::AreEqual(std::int32_t(6), dat.GetInt());
			actions.Update(t);
			Assert::AreEqual(std::int32_t(7), dat.GetInt());
			actions.SetCondition(false);
			actions.Update(t);
			Assert::AreEqual(std::int32_t(7), dat.GetInt());
			actions.Update(t);
			Assert::AreEqual(std::int32_t(7), dat.GetInt());
			Factory<RTTI>::Clear();
		}
	private:
		inline static _CrtMemState _startMemState;
	};
}