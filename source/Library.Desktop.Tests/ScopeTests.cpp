#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"
#include "Foo.h"
#include "ToStringSpecializations.h"
//

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<Datum::DatumTypes>(const Datum::DatumTypes& t)
	{
		try
		{
			switch (t)
			{
			case Datum::DatumTypes::Unknown:
				return L"Unknown"s;
				break;
			case Datum::DatumTypes::Integer:
				return L"Integer"s;
				break;
			case Datum::DatumTypes::Float:
				return L"Float"s;
				break;
			case Datum::DatumTypes::Vector:
				return L"Vector"s;
				break;
			case Datum::DatumTypes::Matrix:
				return L"Matrix"s;
				break;
			case Datum::DatumTypes::String:
				return L"String"s;
				break;
			case Datum::DatumTypes::Pointer:
				return L"Pointer"s;
				break;
			case Datum::DatumTypes::Table:
				return L"Table"s;
				break;
			default:
				return L"error"s;
				break;
			}
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}


	template<>
	inline std::wstring ToString<Datum>(const Datum& t)
	{
		try
		{
			return ToString(t.Type());
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}

	template<>
	inline std::wstring ToString<Datum>(const Datum* t)
	{
		try
		{
			return ToString((*t).Type());
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}

	template<>
	inline std::wstring ToString<Scope>(const Scope& t)
	{
		try
		{
			return ToString(t.ToString());
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}

	template<>
	inline std::wstring ToString<Scope>(Scope* t)
	{
		try
		{
			return ToString((*t).ToString());
		}
		catch (const std::exception&)
		{
			return L"error"s;
		}
	}

}

namespace LibraryDesktopTests
{
	TEST_CLASS(ScopeTests)
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
			Scope s;
			Assert::IsTrue(s.GetParent() == nullptr);
		}

		TEST_METHOD(CopyConstructor)
		{
			const string s1 = "Brian";
			const string s2 = "Stewie";
			const string s3 = "Meg";
			glm::vec4 vec = glm::vec4(4);
			
			Scope s;
			Datum& dat = s.Append(s1);
			dat = "Lois"s;
			Datum& anotherDat = s.Append(s2);
			anotherDat = vec;
			Scope& anotherS = s.AppendScope(s3);

			{
				Assert::IsTrue(s[0] == "Lois"s);
				Assert::IsTrue(s[1] == vec);
				Assert::AreEqual(size_t(3), s.Size());
				auto [datum, index] = s.FindContainedScope(anotherS);
				Assert::IsNotNull(datum);
				Assert::AreSame(anotherS, datum->GetTable());
				Assert::AreEqual(std::size_t(0), index);
			}

			{
				Scope copyScope(s);
				Assert::AreEqual(s, copyScope);
				Assert::AreEqual(std::size_t(3), s.Size());
				Assert::AreEqual(std::size_t(3), copyScope.Size());
				Assert::AreEqual(anotherS, copyScope[2].GetTable());
				Assert::AreEqual(s[0],copyScope[0]);
				Assert::AreEqual(s[1], copyScope[1]);
				Assert::AreEqual(s[2], copyScope[2]);
				Assert::IsTrue(copyScope[0] == "Lois"s);
				Assert::IsTrue(copyScope[1] == anotherDat);
				auto [datum, index] = copyScope.FindContainedScope(anotherS);
				Assert::IsNotNull(datum);
				Assert::AreEqual(anotherS, datum->GetTable());
				Assert::AreEqual(std::size_t(0), index);
			}
		}

		TEST_METHOD(MoveConstructorAssignment)
		{
			const string s1 = "Brian";
			const string s2 = "Stewie";
			const string s3 = "Meg";
			const string s4 = "Peter";
			const string s5 = "Chris";
			glm::vec4 vec = glm::vec4(4);

			{
				Scope s;
				Datum& dat = s.Append(s1);
				dat = "Lois"s;
				Datum& anotherDat = s.Append(s2);
				anotherDat = vec;
				Scope& anotherS = s.AppendScope(s3);

				Scope newScope;
				Datum& newDat = newScope.Append(s4);
				newDat = 8;
				newScope.AppendScope(s5);
				Assert::AreEqual(size_t(2), newScope.Size());

				newScope = std::move(s);
				
				Assert::IsTrue(newScope[0] == "Lois"s);
				Assert::IsTrue(newScope[1] == vec);
				Assert::AreEqual(size_t(3), newScope.Size());
				auto [datum, index] = newScope.FindContainedScope(anotherS);
				Assert::IsNotNull(datum);
				Assert::AreSame(anotherS, datum->GetTable());
				Assert::AreEqual(std::size_t(0), index);

			}

			{
				Scope s;
				Datum& dat = s.Append(s1);
				dat = "Lois"s;
				Datum& anotherDat = s.Append(s2);
				anotherDat = vec;
				Scope& anotherS = s.AppendScope(s3);
				Scope copyScope(std::move(s));

				Assert::IsTrue(copyScope[0] == "Lois"s);
				Assert::IsTrue(copyScope[1] == vec);
				Assert::AreEqual(size_t(3), copyScope.Size());
				auto [datum, index] = copyScope.FindContainedScope(anotherS);
				Assert::IsNotNull(datum);
				Assert::AreSame(anotherS, datum->GetTable());
				Assert::AreEqual(std::size_t(0), index);

			}

			{
				Scope s;
				Datum& dat = s.Append(s1);
				dat = "Lois"s;
				Scope copyScope(std::move(s));

				Assert::IsTrue(copyScope[0] == "Lois"s);
				Assert::AreEqual(size_t(1), copyScope.Size());

			}

			{
				Scope s;
				Datum& dat = s.Append(s1);
				dat = "Lois"s;
				Datum& anotherDat = s.Append(s2);
				anotherDat = vec;
				Scope& anotherS = s.AppendScope(s3);

				Assert::IsTrue(s[0] == "Lois"s);
				Assert::IsTrue(s[1] == vec);
				Assert::AreEqual(size_t(3), s.Size());
				auto [datum, index] = s.FindContainedScope(anotherS);
				Assert::IsNotNull(datum);
				Assert::AreSame(anotherS, datum->GetTable());
				Assert::AreEqual(std::size_t(0), index);

			}


		}

		TEST_METHOD(EquivalenceOperators)
		{
			const string s1 = "Brian";
			const string s2 = "Stewie";
			const string s3 = "Meg";
			glm::vec4 vec = glm::vec4(4);

			{
				Scope s;
				Scope copyS(s);
				Assert::AreEqual(s, copyS);
			}

			{
				Scope scope;
				Datum& oneDatum = scope.Append(s1);
				oneDatum = "Lois"s;
				Datum& threeDatum = scope.Append(s2);
				threeDatum = vec;
				scope.AppendScope(s3);
				Scope scopeTwo;
				scopeTwo.Append(s3);
				Scope copyScope = scope;
				Assert::IsTrue(scope != scopeTwo);
				Assert::AreEqual(scope, copyScope);
			}
		}
		TEST_METHOD(Clone)
		{
			const string s1 = "Brian"s;
			const string s2 = "Stewie"s;
			const string s3 = "Meg"s;
			glm::vec4 vec = glm::vec4(4);

			{
				Scope scope;
				Datum& oneDatum = scope.Append(s1);
				oneDatum = "Lois"s;
				Datum& twoDatum = scope.Append(s2);
				twoDatum = vec;
				scope.AppendScope(s3);
				Scope* clonedScope = scope.Clone();
				Assert::AreEqual(clonedScope->Size(), std::size_t(3));
				delete clonedScope;
			}

		}
		TEST_METHOD(Find)
		{
			const string s1 = "Brian"s;
			const string s2 = "Stewie"s;
			const string s3 = "Meg"s;
			glm::vec4 vec = glm::vec4(4);

			{
				Scope scope;
				Datum& oneDatum = scope.Append(s1);
				oneDatum = "Lois"s;
				Datum& twoDatum = scope.Append(s2);
				twoDatum = vec;
				Assert::IsNull(scope.Find(s3));
				Assert::AreEqual(std::size_t(2), scope.Size());
				Assert::AreEqual(*scope.Find(s1), oneDatum);
				Assert::AreEqual(*scope.Find(s2), twoDatum);
				const Scope constCopyScope(scope);
				Assert::IsNull(constCopyScope.Find(s3));
				Assert::AreEqual(std::size_t(2), constCopyScope.Size());
				Assert::AreEqual(*constCopyScope.Find(s1), oneDatum);
				Assert::AreEqual(*constCopyScope.Find(s2), twoDatum);
			}
		}

		TEST_METHOD(Search)
		{
			const string showName = "FamilyGuy"s;
			const string s1 = "Brian"s;
			const string s2 = "Stewie"s;
			const string s3 = "Meg"s;
			const string s4 = "Lois"s;
			glm::vec4 vec = glm::vec4(4);

			{
				Scope scope;
				Datum& oneDatum = scope.Append(showName);
				oneDatum = 3;
				Scope& actorOne = scope.AppendScope(s1);
				Scope& actorTwo = actorOne.AppendScope(s2);
				Scope& actorThree = actorTwo.AppendScope(s3);
				{
					Scope* search;
					Assert::AreEqual(oneDatum, *scope.Find(showName));
					Assert::AreEqual(*actorThree.Search(showName), oneDatum);
					Assert::IsNull(actorThree.Search(s4));
					Assert::IsNull(actorThree.Search(s4, search));
				}

				{
					const Scope* search;
					Assert::AreEqual(oneDatum, *scope.Find(showName));
					Assert::AreEqual(*const_cast<const Scope&>(actorThree).Search(showName), oneDatum);
					Assert::IsNull(const_cast<const Scope&>(actorThree).Search(s4));
					Assert::IsNull(const_cast<const Scope&>(actorThree).Search(s4, search));
				}
			}
		}

		TEST_METHOD(Append)
		{
			const string showName = "FamilyGuy"s;
			const string s1 = "Brian"s;
			const string s2 = "Stewie"s;
			const string s3 = "Meg"s;
			const string s4 = "Lois"s;
			glm::vec4 vec = glm::vec4(4);

			{
				Scope scope;
				Datum& oneDatum = scope.Append(showName);
				oneDatum = 3.78f;
				Assert::AreEqual(3.78f, scope[0].GetFloat());
				Datum& twoDatum = scope.Append(showName);
				Assert::AreEqual(oneDatum, twoDatum);
			}
		}

		TEST_METHOD(AppendScope)
		{
			const string showName = "FamilyGuy"s;
			const string s1 = "Brian"s;
			const string s2 = "Stewie"s;
			{
				Scope scope;
				Datum& oneDatum = scope.Append(s1);
				oneDatum = 3.78f;

				Scope scopeTwo;
				Scope& newScope = scopeTwo.AppendScope(showName);
				newScope = scope;
				Assert::AreEqual(newScope, scopeTwo[0].GetTable());
				scopeTwo.AppendScope(showName);
				Assert::AreEqual(scopeTwo.Size(), size_t(1));
			}

		}

		TEST_METHOD(Adopt)
		{
			{
				const string s1 = "Brian"s;
				const string s2 = "Stewie"s;
				Scope scope;
				scope.AppendScope(s2);

				Scope anotherScope;
				Scope& kidScope = anotherScope.AppendScope(s1);

				scope.Adopt(kidScope, s2);
				Assert::AreEqual(scope.Size(), size_t(1));
				Assert::AreEqual(kidScope, scope[0].GetTable(1));
			}

			{
				const string s1 = "Brian"s;
				const string s2 = "Stewie"s;
				Scope scope;

				Scope anotherScope;
				Scope& kidScope = anotherScope.AppendScope(s1);

				scope.Adopt(kidScope, s2);
				Assert::AreEqual(scope.Size(), size_t(1));
				Assert::AreEqual(kidScope, scope[0].GetTable());
			}

		}

		TEST_METHOD(SquareBracketOperators)
		{
			{
				const string s1 = "Brian"s;

				Scope scope;
				Scope* scopePointer = &scope;
				Datum& d = scope.Append(s1);
				d = 7.895f;
				Assert::AreEqual(d, (* const_cast<const Scope*>(scopePointer))[0]);
			}

			{
				const string s1 = "Brian"s;

				Scope scope;
				Datum& d = scope.Append(s1);
				d = 7.895f;
				Assert::AreEqual(d, scope[0]);
			}

			{
				const string s1 = "Brian"s;
			
				Scope scope;
				Datum& d = scope.Append(s1);
				d = 7.895f;
				Assert::AreEqual(d, scope[s1]);
			}


		}

		TEST_METHOD(FindContainedScope)
		{
			{
				const string s1 = "Brian"s;

				Scope scope;
				//Scope& kidScope = scope.AppendScope(s1);
				//Assert::AreEqual(scope.FindContainedScope(kidScope).first, &scope[0]);
			}
		}

		TEST_METHOD(Clear)
		{
			{
				const string s1 = "Brian";
				const string s2 = "Stewie";
				const string s3 = "Meg";
				glm::vec4 vec = glm::vec4(4);
				
				Scope s;
				Datum& dat = s.Append(s1);
				dat = "Lois"s;
				Datum& anotherDat = s.Append(s2);
				anotherDat = vec;
				s.AppendScope(s3);
				Assert::AreEqual(s.Size(), size_t(3));
				s.Clear();
				Assert::AreEqual(s.Size(), size_t(0));
				Assert::IsNull(s.Find(s1));
				Assert::IsNull(s.Find(s2));
				Assert::IsNull(s.Find(s3));
			}
		}


		TEST_METHOD(Orphan)
		{
			{
				const string s1 = "Brian"s;
				const string s2 = "Stewie"s;
				const string s3 = "Peter"s;
				const string s4 = "Lois"s;
				const string s5 = "Brian"s;
				const string s6 = "Stewie"s;
				glm::vec4 vec = glm::vec4(4);

				Scope anotherScope;
				Scope& anotherChild = anotherScope.AppendScope(s6);
				Datum& dat = anotherChild.Append(s5);
				dat = 8;

				Scope scope;
				Datum& datTwo = scope.Append(s1);
				datTwo = "Carter"s;
				Datum& datThree = scope.Append(s2);
				datThree = vec;
				scope.Adopt(anotherChild, s3);
				Scope& kidOne = scope.Find(s3)->GetTable();
				Scope& kidTwo = scope.AppendScope(s3);

				Assert::AreEqual(scope.Size(), std::size_t(3));
				Assert::AreEqual(scope[2].Size(), std::size_t(2));
				scope.Orphan(kidOne);
				delete& kidOne;
				Assert::AreEqual(scope.Size(), std::size_t(3));
				Assert::IsNull(scope.FindContainedScope(kidOne).first);
				Assert::AreEqual(scope[2].Size(), std::size_t(1));
				scope.Orphan(kidTwo);
				Assert::AreEqual(scope.Size(), std::size_t(3));
				Assert::IsNotNull(scope.Find(s3));
			}
		}


	private:
		inline static _CrtMemState _startMemState;
	};
}