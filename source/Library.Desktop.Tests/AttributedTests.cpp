#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "AttributedFoo.h"
#include "TypeRegistry.h"
#include "Attributed.h"

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

	template<>
	inline std::wstring ToString<AttributedFoo>(const AttributedFoo& t)
	{
		RETURN_WIDE_STRING(&t);
	}
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AttributedTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
			TypeRegistry::CreateInstance();
			TypeRegistry::InsertType(AttributedFoo::TypeIdClass(), AttributedFoo::Signatures());
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
			Scope s;
			Foo f;
			AttributedFoo af;
			AttributedFoo afTwo;

			Assert::IsTrue(af.Is(af.TypeIdClass()));
			Assert::IsTrue(af.Is(s.TypeIdClass()));
			Assert::IsFalse(af.Is(f.TypeIdClass()));
			Assert::IsTrue(af.Equals(&afTwo));
			Assert::IsFalse(af.Equals(&s));
			Assert::IsFalse(af.Equals(&f));
		}

		TEST_METHOD(Constructor)
		{
			AttributedFoo af;
			Assert::IsTrue(af["ExternalInteger"] == af.ExternalInteger);
			Assert::IsTrue(af["this"] == &af);
			af.ExternalInteger = 157;
			Assert::IsTrue(af["ExternalInteger"] == af.ExternalInteger);
			af.ExternalFloat = 157.56f;
			Assert::IsTrue(af["ExternalFloat"] == af.ExternalFloat);
			af.ExternalString = "Lois";
			Assert::IsTrue(af["ExternalString"] == af.ExternalString);
		}

		TEST_METHOD(Move)
		{
			AttributedFoo af;
			af.ExternalInteger = 895;
			AttributedFoo copyAf = af;
			AttributedFoo movedAf = std::move(copyAf);
			Assert::AreEqual(movedAf,af);
			movedAf.ExternalString = "Lois"s;
			Assert::IsTrue(movedAf["ExternalString"] == movedAf.ExternalString);

			AttributedFoo copyAfTwo = af;
			movedAf = std::move(copyAfTwo);
			movedAf.ExternalString = "Lois"s;
			Assert::IsTrue(movedAf["ExternalString"] == movedAf.ExternalString);

		}

		TEST_METHOD(Copy)
		{
			AttributedFoo af;
			af.ExternalInteger = 895;



			AttributedFoo copyAf = af;
			Assert::AreEqual(copyAf, af);
			af.ExternalString = "Lois";
			Assert::AreNotEqual(copyAf, af);

			copyAf = af;
			Assert::AreEqual(af.ExternalString, copyAf.ExternalString);
			
		}

		TEST_METHOD(AttributeCheck)
		{
			AttributedFoo af;
			Assert::IsFalse(af.IsAttribute("FamilyGuy"));
			Assert::IsTrue(af.IsAttribute("ExternalInteger"));
			Assert::IsTrue(af.IsAttribute("ExternalFloat"));
			Assert::IsTrue(af.IsAttribute("ExternalString"));
			Assert::IsTrue(af.IsAttribute("ExternalVector"));
			Assert::IsTrue(af.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(af.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(af.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(af.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(af.IsAttribute("ExternalMatrixArray"));
			Assert::IsTrue(af.IsAttribute("NestedScope"));
			Assert::IsTrue(af.IsAttribute("NestedScopeArray"));	
		}

		TEST_METHOD(AppendCheck)
		{
			AttributedFoo af;
			af.AppendAuxiliaryAttribute("Lois") = 200;
			Assert::IsTrue(af.IsAuxiliaryAttribute("Lois"));
			Assert::IsFalse(af.IsAuxiliaryAttribute("Peter"));
			Assert::IsFalse(af.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsTrue(af["Lois"] == 200);
			af.AppendAuxiliaryAttribute("Lois") = 526;
			Assert::IsTrue(af["Lois"] == 526);
			Assert::ExpectException<std::runtime_error>([&af] {af.AppendAuxiliaryAttribute("ExternalInteger"); });
	
		}

		TEST_METHOD(PrescibedAuxiliaryAttribute)
		{
			AttributedFoo af;
			Assert::IsTrue(af.AuxiliaryAttributes().IsEmpty());
			auto atri = af.Attributes();
			Assert::AreEqual(atri[0]->first, "this"s);
			Assert::IsTrue(atri[0]->second == &af);
			Assert::AreEqual(atri[1]->first, "ExternalInteger"s);
			Assert::IsTrue(atri[1]->second == af[1]);
			Assert::AreEqual(atri.Size(), af.Size());
			af.AppendAuxiliaryAttribute("Lois") = 200;
			af.AppendAuxiliaryAttribute("Peter") = "Chris";
			
			
			auto prescribedAttributes = af.PrescribedAttributes();
			Assert::AreEqual(prescribedAttributes.Size(), af.Size()-2);

			AttributedFoo afTwo;
			auto prescribedAttributesTwo = afTwo.PrescribedAttributes();
			Assert::AreEqual(prescribedAttributesTwo.Size(), afTwo.Size());


			auto auxAttributes = af.AuxiliaryAttributes();
			Assert::AreEqual(auxAttributes[0]->first, "Lois"s);
			Assert::IsTrue(auxAttributes[0]->second == 200);
			Assert::AreEqual(auxAttributes[1]->first, "Peter"s);
			Assert::IsTrue(auxAttributes[1]->second == "Chris"s);
			Assert::AreEqual(auxAttributes.Size(), size_t(2));
		}

		TEST_METHOD(PrescibedAuxiliaryAttributeCheck)
		{
			AttributedFoo af;
			Assert::IsFalse(af.IsPrescribedAttribute("FamilyGuy"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(af.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(af.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(af.IsPrescribedAttribute("NestedScopeArray"));

			af.AppendAuxiliaryAttribute("Lois");
			Assert::IsTrue(af.IsAuxiliaryAttribute("Lois"));
			Assert::IsFalse(af.IsAuxiliaryAttribute("Peter"));
			Assert::IsFalse(af.IsAuxiliaryAttribute("ExternalFloatArray"));
		}
	private:
		inline static _CrtMemState _startMemState;
	};
}

