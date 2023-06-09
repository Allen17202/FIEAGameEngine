#include "pch.h"
#include "CppUnitTest.h"
#include "IJsonParseHelper.h"
#include "JsonParseHelperInteger.h"
#include "JsonParseCoordinator.h"
#include "TypeRegistry.h"
#include "ToStringSpecializations.h"
#include "DefaultEquality.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	std::wstring ToString<JsonParseCoordinator>(JsonParseCoordinator* t)
	{
		try
		{
			t;
			return L"Parse Coordinator";
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(JsonParseCoordinatorTests)
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

		TEST_METHOD(Constructor)
		{
			{
				std::string temp = R"({ "integer": 5275 })";
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);
				manager.DeserializeObject(temp);
				Assert::AreEqual(size_t(0), manager.HelperGetter().Size());
				Assert::AreEqual(size_t(0), manager.GetWrapper()->Depth());
			}

			{
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);
				Assert::AreEqual(size_t(0), manager.GetWrapper()->Depth());
			}

			{
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);

				Assert::AreEqual(contain->GetJsonParseCoordinator(), &manager);
				Assert::AreEqual(size_t(0), contain->_data.Size());
				Assert::AreEqual(size_t(0), manager.HelperGetter().Size());
				Assert::IsFalse(manager.isClone());
			}
		}

		TEST_METHOD(Cloning)
		{
			std::string temp = R"({ "integer": 5275 })";
			JsonParseHelperInteger::SharedDataContainer container;
			auto contain = &container;
			JsonParseCoordinator manager(contain);
			std::shared_ptr<JsonParseHelperInteger> intHelper = std::make_shared<JsonParseHelperInteger>();
			
			manager.AddHelper(intHelper);
			manager.DeserializeObject(temp);
			Assert::AreEqual(contain->GetJsonParseCoordinator(), &manager);
			Assert::AreEqual(size_t(1), contain->_data.Size());
			Assert::AreEqual(size_t(1), manager.HelperGetter().Size());
			Assert::AreEqual(contain->_data.Front(), 5275);
			Assert::IsFalse(manager.isClone());

			JsonParseCoordinator* anotherManager = manager.Clone();
			Assert::AreEqual(size_t(1), contain->_data.Size());
			Assert::AreEqual(size_t(1), anotherManager->HelperGetter().Size());
			Assert::AreEqual(size_t(0), anotherManager->GetWrapper()->Depth());
			Assert::AreEqual(contain->_data.Front(), 5275);
			Assert::IsTrue(anotherManager->isClone());
			delete anotherManager;	
		}

		TEST_METHOD(Move)
		{
			{
				std::string temp = R"({ "integer": 5275 })";
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);
				std::shared_ptr<JsonParseHelperInteger> intHelper = std::make_shared<JsonParseHelperInteger>();
				manager.AddHelper(intHelper);
				manager.DeserializeObject(temp);

				Assert::AreEqual(contain->GetJsonParseCoordinator(), &manager);
				Assert::AreEqual(size_t(1), contain->_data.Size());
				Assert::AreEqual(size_t(1), manager.HelperGetter().Size());
				Assert::AreEqual(contain->_data.Front(), 5275);
				Assert::IsFalse(manager.isClone());

				JsonParseCoordinator anotherManager(std::move(manager));
				Assert::AreEqual(contain->GetJsonParseCoordinator(), &anotherManager);
				Assert::AreEqual(size_t(1), contain->_data.Size());
				Assert::AreEqual(size_t(1), anotherManager.HelperGetter().Size());
				Assert::AreEqual(contain->_data.Front(), 5275);
				Assert::IsFalse(anotherManager.isClone());
			}

			{
				std::string temp = R"({ "integer": 5275 })";
				std::string tempTwo = R"({ "integer": 98524 })";
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);
				std::shared_ptr<JsonParseHelperInteger> intHelper = std::make_shared<JsonParseHelperInteger>();
				manager.AddHelper(intHelper);

				JsonParseHelperInteger::SharedDataContainer anotherContainer;
				auto anotherContain = &anotherContainer;
				JsonParseCoordinator anotherManager(anotherContain);
				std::shared_ptr<JsonParseHelperInteger> anotherIntHelper = std::make_shared<JsonParseHelperInteger>();
				anotherManager.AddHelper(anotherIntHelper);

				manager.DeserializeObject(temp);
				Assert::AreEqual(contain->GetJsonParseCoordinator(), &manager);
				Assert::AreEqual(size_t(1), contain->_data.Size());
				Assert::AreEqual(size_t(1), manager.HelperGetter().Size());
				Assert::AreEqual(contain->_data.Front(), 5275);
				Assert::IsFalse(manager.isClone());

				anotherManager.DeserializeObject(tempTwo);
				Assert::AreEqual(anotherContain->GetJsonParseCoordinator(), &anotherManager);
				Assert::AreEqual(size_t(1), anotherContain->_data.Size());
				Assert::AreEqual(size_t(1), anotherManager.HelperGetter().Size());
				Assert::AreEqual(anotherContain->_data.Front(), 98524);
				Assert::IsFalse(anotherManager.isClone());


				JsonParseCoordinator& cloneManager = *manager.Clone();
				Assert::AreEqual(size_t(1), anotherContain->_data.Size());
				Assert::AreEqual(size_t(1), cloneManager.HelperGetter().Size());
				Assert::AreEqual(size_t(0), cloneManager.GetWrapper()->Depth());
				Assert::AreEqual(contain->_data.Front(), 5275);
				Assert::IsTrue(cloneManager.isClone());
				
				anotherManager = std::move(cloneManager);
				Assert::AreEqual(anotherContain->GetJsonParseCoordinator(), &anotherManager);
				Assert::AreEqual(size_t(1), anotherContain->_data.Size());
				Assert::AreEqual(size_t(1), anotherManager.HelperGetter().Size());
				Assert::AreEqual(size_t(0), anotherManager.GetWrapper()->Depth());
				Assert::AreEqual(anotherContain->_data.Front(), 98524);
				Assert::IsTrue(anotherManager.isClone());
			}
		}

		TEST_METHOD(Helper)
		{
			{
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);
				std::shared_ptr<JsonParseHelperInteger> intHelper = std::make_shared<JsonParseHelperInteger>();
				manager.AddHelper(intHelper);
				Assert::AreEqual(size_t(1), manager.HelperGetter().Size());
				manager.RemoveHelper(intHelper);
				Assert::AreEqual(size_t(0), manager.HelperGetter().Size());

			}

			{
				std::string temp = R"({ "integer": 5275 })";
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);
				std::shared_ptr<JsonParseHelperInteger> intHelper = std::make_shared<JsonParseHelperInteger>();
				manager.AddHelper(intHelper);
				manager.DeserializeObject(temp);
				Assert::AreEqual(contain->GetJsonParseCoordinator(), &manager);
				Assert::AreEqual(size_t(1), contain->_data.Size());
				Assert::AreEqual(size_t(1), manager.HelperGetter().Size());
				Assert::AreEqual(contain->_data.Front(), 5275);
				Assert::IsFalse(manager.isClone());


				JsonParseCoordinator& anotherManager = *manager.Clone();
				Assert::AreEqual(size_t(1), contain->_data.Size());
				Assert::AreEqual(size_t(1), anotherManager.HelperGetter().Size());
				Assert::AreEqual(contain->_data.Front(), 5275);
				Assert::IsTrue(anotherManager.isClone());

				std::shared_ptr<JsonParseHelperInteger> lastIntHelper = std::make_shared<JsonParseHelperInteger>();
				anotherManager.AddHelper(lastIntHelper);
				Assert::AreEqual(size_t(2), anotherManager.HelperGetter().Size());

				std::shared_ptr<IJsonParseHelper> clonedIntHelper = anotherManager.HelperGetter().At(0);
				anotherManager.RemoveHelper(clonedIntHelper);
				Assert::AreEqual(size_t(1), anotherManager.HelperGetter().Size());
				delete& anotherManager;
			}

			{
				std::string temp = R"(JsonFiles\intTest.json)"s;
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);
				std::shared_ptr<JsonParseHelperInteger> intHelper = std::make_shared<JsonParseHelperInteger>();
				manager.AddHelper(intHelper);
				manager.DeserializeObjectFromFile(temp);
				Assert::AreEqual(contain->GetJsonParseCoordinator(), &manager);
				Assert::AreEqual(size_t(1), contain->_data.Size());
				Assert::AreEqual(size_t(1), manager.HelperGetter().Size());
				Assert::AreEqual(contain->_data.Front(), 502);
				Assert::IsFalse(manager.isClone());
			}
		}

		TEST_METHOD(SharedData)
		{
			{
				std::string temp = R"({ "integer": 5275 })";
				JsonParseHelperInteger::SharedDataContainer container;
				auto contain = &container;
				JsonParseCoordinator manager(contain);
				std::shared_ptr<JsonParseHelperInteger> intHelper = std::make_shared<JsonParseHelperInteger>();
				manager.AddHelper(intHelper);
				manager.DeserializeObject(temp);

				Assert::AreEqual(contain->GetJsonParseCoordinator(), &manager);
				Assert::AreEqual(size_t(1), contain->_data.Size());
				Assert::AreEqual(size_t(1), manager.HelperGetter().Size());
				Assert::AreEqual(contain->_data.Front(), 5275);
				Assert::IsFalse(manager.isClone());

				Assert::ExpectException<std::runtime_error>([&manager]() {manager.SetWrapper(nullptr); });


				JsonParseHelperInteger::SharedDataContainer anotherContainer;
				auto containTwo = &anotherContainer;
				manager.SetWrapper(containTwo);
				JsonParseCoordinator::SharedDataContainer* pointerContainer = manager.GetWrapper();
				Assert::IsTrue(containTwo == pointerContainer);
			}

		}
	private:
		inline static _CrtMemState _startMemState;
	};
}