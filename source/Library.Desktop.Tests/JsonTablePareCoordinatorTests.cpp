#include "pch.h"
#include "CppUnitTest.h"
#include "IJsonParseHelper.h"
#include "JsonParseCoordinator.h"
#include "JsonTableParseHelper.h"
#include "TypeRegistry.h"
#include "ToStringSpecializations.h"
#include <crtdbg.h>
#include <glm\glm.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;
using namespace FIEAGameEngine;


namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	std::wstring ToString<Datum::DatumTypes>(const Datum::DatumTypes& d)
	{
		const std::string& typeString = Datum::_datumTypesStringMap.At(d);
		RETURN_WIDE_STRING(typeString.c_str());
	}
}


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(JsonTableParseCoordinatorTests)
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

		TEST_METHOD(ParseScope)
		{
			{
				std::string temp = R"({
					"MyName": {
						"type": "string",
						"value": "Gregory"
					},
					"RandomInts": {
						"type": "integer",
						"value": [ 43, 7583, 74397 ]
					},
					"FamilyGuy": {
                          "type": "table",
                          "value": {
                               "Character": {
                                    "type": "string",
                                    "value": "Lois"
                                },
								"CharacterTwo": {
                                    "type": "integer",
                                    "value": 985
                                }
							}
                      }
			})";

				Scope s;
				auto s2 = &s;
				JsonTableParseHelper::SharedDataContainer container(s2);
				auto anotherContainer = &container;
				JsonParseCoordinator manager(anotherContainer);
				auto helper = std::make_shared<JsonTableParseHelper>();
				manager.AddHelper(helper);
				manager.DeserializeObject(temp);

				Assert::IsNotNull(s2->Find("MyName"));
				Assert::AreEqual(Datum::DatumTypes::String, s2->Find("MyName")->Type());
				Assert::AreEqual("Gregory"s, s2->Find("MyName")->FrontString());

				Assert::IsNotNull(s2->Find("RandomInts"));
				Assert::AreEqual(Datum::DatumTypes::Integer, s2->Find("RandomInts")->Type());
				Assert::AreEqual(43, s2->Find("RandomInts")->FrontInt());
				Assert::AreEqual(74397, s2->Find("RandomInts")->BackInt());

				Assert::IsNotNull(s2->Find("FamilyGuy"));
				Assert::AreEqual(Datum::DatumTypes::Table, s2->Find("FamilyGuy")->Type());
				Assert::IsNotNull(s2->Find("FamilyGuy")->GetTable().Find("Character"));
				Assert::IsNotNull(s2->Find("FamilyGuy")->GetTable().Find("CharacterTwo"));
			}

			{
				std::string temp = R"(JsonFiles\ScopeTest.json)"s;
				Scope s;
				auto s2 = &s;
				JsonTableParseHelper::SharedDataContainer container(s2);
				auto anotherContainer = &container;
				JsonParseCoordinator manager(anotherContainer);
				auto helper = std::make_shared<JsonTableParseHelper>();
				manager.AddHelper(helper);
				manager.DeserializeObjectFromFile(temp);

				Assert::IsNotNull(s2->Find("MyName"));
				Assert::AreEqual(Datum::DatumTypes::String, s2->Find("MyName")->Type());
				Assert::AreEqual("Gregory"s, s2->Find("MyName")->FrontString());

				Assert::IsNotNull(s2->Find("RandomInts"));
				Assert::AreEqual(Datum::DatumTypes::Integer, s2->Find("RandomInts")->Type());
				Assert::AreEqual(43, s2->Find("RandomInts")->FrontInt());
				Assert::AreEqual(74397, s2->Find("RandomInts")->BackInt());

				Assert::IsNotNull(s2->Find("FamilyGuy"));
				Assert::AreEqual(Datum::DatumTypes::Table, s2->Find("FamilyGuy")->Type());
				Assert::IsNotNull(s2->Find("FamilyGuy")->GetTable().Find("Character"));
				Assert::IsNotNull(s2->Find("FamilyGuy")->GetTable().Find("CharacterTwo"));
			}
		}


	private:
		inline static _CrtMemState _startMemState;
	};
}