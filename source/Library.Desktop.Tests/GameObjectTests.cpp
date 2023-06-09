#include "pch.h"
#include "CppUnitTest.h"
#include "Factory.h"
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
	inline std::wstring ToString<glm::vec4>(const glm::vec4& other)
	{
		try
		{
			return L"vec4("s + ToString(other.x) + L", "s + ToString(other.y) + L", "s + ToString(other.z) + L", "s + ToString(other.w) + L")"s;
		}
		catch(const std::exception&)
		{
			return L"error"s;
		}
	}

	template<>
	std::wstring ToString<Datum::DatumTypes>(const Datum::DatumTypes& d)
	{
		const std::string& typeString = Datum::_datumTypesStringMap.At(d);
		RETURN_WIDE_STRING(typeString.c_str());
	}
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(GameObjectTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);

			TypeRegistry::CreateInstance();
			TypeRegistry::InsertType(GameObject::TypeIdClass(), GameObject::Signatures());
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

		TEST_METHOD(ConstructorCheck)
		{
			GameObject g;
			Assert::IsNotNull(g.Find("this"));
			Assert::IsNotNull(g.Find("Name"));
			Assert::IsNotNull(g.Find("Position"));
			Assert::IsNotNull(g.Find("Rotation"));
			Assert::IsNotNull(g.Find("Scale"));
			Assert::IsNotNull(g.Find("Children"));
		}

		TEST_METHOD(ParseGameObject)
		{
			std::string temp = R"(JsonFiles\GameObject.json)"s;
			GameObject g;
			Factory<Scope>::Add(std::make_shared<FIEAGameEngine::GameObjectFactory>());
			JsonTableParseHelper::SharedDataContainer container(&g);
			JsonParseCoordinator manager(&container);
			auto helper = std::make_shared<JsonTableParseHelper>();
			manager.AddHelper(helper);
			manager.DeserializeObjectFromFile(temp);

			Assert::IsNotNull(g.Find("this"));
			Assert::IsNotNull(g.Find("Name"));
			Assert::IsNotNull(g.Find("Position"));
			Assert::IsNotNull(g.Find("Rotation"));
			Assert::IsNotNull(g.Find("Scale"));
			Assert::IsNotNull(g.Find("Children"));
			Assert::IsNotNull(g.Find("Actions"));
			Assert::AreEqual(std::size_t(0), container.Depth());
			Assert::AreEqual(std::size_t(7), g.Size());

			Assert::AreEqual(Datum::DatumTypes::String, g.Find("Name")->Type());
			Assert::AreEqual(Datum::DatumTypes::Vector, g.Find("Position")->Type());
			Assert::AreEqual(Datum::DatumTypes::Vector, g.Find("Rotation")->Type());
			Assert::AreEqual(Datum::DatumTypes::Vector, g.Find("Scale")->Type());
			Assert::AreEqual(Datum::DatumTypes::Table, g.Find("Children")->Type());

			glm::vec4 pos(1, 2, 3, 4);
			glm::vec4 rot(5, 6, 7, 8);
			glm::vec4 scale(9, 10, 11, 12);

			Assert::AreEqual(g.Find("Name")->FrontString(), "Gregory"s);
			Assert::AreEqual(g.Find("Position")->FrontVector(), pos);
			Assert::AreEqual(g.Find("Rotation")->FrontVector(), rot);
			Assert::AreEqual(g.Find("Scale")->FrontVector(), scale);
			Assert::IsNotNull(g.Find("Children")->GetTable(0).Find("Name"));
			Assert::IsNotNull(g.Find("Children")->GetTable(1).Find("Name"));
			Assert::AreEqual(g.GetChildAtIndex(0).ToString(), "Lois"s);
			Assert::AreEqual(g.GetChildAtIndex(1).ToString(), "Peter"s);
		

			//GameObject f = g;
			//Assert::IsTrue(f.Equals(g));
			/*GameTime* t;
			g.Update(*t);
			delete t;*/
			Factory<Scope>::Clear();
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}