#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"
#include "Foo.h"
#include "RTTI.h"
#include "ToStringSpecializations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;


namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<Datum::DatumTypes>(const Datum::DatumTypes& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<Datum::DatumTypes>(const Datum::DatumTypes* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<Datum::DatumTypes>(Datum::DatumTypes* t)
	{
		RETURN_WIDE_STRING(t);
	}


	template<>
	inline std::wstring ToString<glm::vec4>(const glm::vec4& t)
	{
		t;
		RETURN_WIDE_STRING("Vec4");
	}

	template<>
	inline std::wstring ToString<glm::vec4>(const glm::vec4* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<glm::vec4>(glm::vec4* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<glm::mat4>(const glm::mat4& t)
	{
		t;
		RETURN_WIDE_STRING("Mat4");
	}

	template<>
	inline std::wstring ToString<glm::mat4>(const glm::mat4* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<glm::mat4>(glm::mat4* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<RTTI>(const RTTI& t)
	{
		t;
		RETURN_WIDE_STRING("RTTI");
	}

	template<>
	inline std::wstring ToString<RTTI>(const RTTI* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<RTTI>(RTTI* t)
	{
		RETURN_WIDE_STRING(t);
	}

}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DatumTests)
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
			Datum a;
			Assert::AreEqual(size_t(0), a.Size());
			Assert::AreEqual(size_t(0), a.Capacity());
			Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
			Assert::IsFalse(a.isExternal());

			{
				Datum b;
				Datum c;
				b = c;
			}
		}

		TEST_METHOD(CopyConstructor)
		{
			{
				Datum a;
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.PushBackInt(10);
				a.PushBackInt(20);
				a.PushBackInt(30);
				a.PushBackInt(40);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
				Datum b(a);
				Assert::AreEqual(a.Size(), b.Size());
				Assert::AreEqual(a.Size(), b.Capacity());
				Assert::AreEqual(a.Type(), b.Type());
			}

			{
				Datum a;
				float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.SetStorageFloat(bits, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Float, a.Type());
				Datum b(a);
				Assert::AreEqual(a.Size(), b.Size());
				Assert::AreEqual(a.Size(), b.Capacity());
				Assert::AreEqual(a.Type(), b.Type());
			}

			{
				const glm::vec4 s1 {10, 20,30,40};
				const glm::vec4 s2{ 1, 2,3,4 };
				Datum a;
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.PushBackVector(s1);
				a.PushBackVector(s2);
				Assert::AreEqual(size_t(2), a.Size());
				Assert::AreEqual(size_t(2), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Vector, a.Type());
				Datum b(a);
				Assert::AreEqual(a.Size(), b.Size());
				Assert::AreEqual(a.Size(), b.Capacity());
				Assert::AreEqual(a.Type(), b.Type());
			}

			{
				const string s1 = "Brian";
				const string s2 = "Stewie";
				Datum a;
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.PushBackString(s1);
				a.PushBackString(s2);
				Assert::AreEqual(size_t(2), a.Size());
				Assert::AreEqual(size_t(2), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::String, a.Type());
				Datum b(a);
				Assert::AreEqual(a.Size(), b.Size());
				Assert::AreEqual(a.Size(), b.Capacity());
				Assert::AreEqual(a.Type(), b.Type());
			}
		}

		
		TEST_METHOD(AssignmentOperatorAndOverloads)
		{
			int boats[]{ 1,2,3,4 };
			float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
			const glm::vec4 s1{ 10, 20,30,40 };
			const glm::vec4 s2{ 1, 2,3,4 };
			const string s3 = "Brian";
			const string s4 = "Stewie";

			{
				Datum a;
				a = 10;
				Assert::AreEqual(size_t(1), a.Size());
				Assert::AreEqual(size_t(1), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
			}

			{
				Datum a;
				a = 10.5f;
				Assert::AreEqual(size_t(1), a.Size());
				Assert::AreEqual(size_t(1), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Float, a.Type());
			}

			{
				Datum a;
				a = s3;
				Assert::AreEqual(size_t(1), a.Size());
				Assert::AreEqual(size_t(1), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::String, a.Type());
			}

			{
				Datum a;
				glm::vec4 temp;
				a = temp;
				Assert::AreEqual(size_t(1), a.Size());
				Assert::AreEqual(size_t(1), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Vector, a.Type());
			}

			{
				Datum a;
				glm::mat4 temp;
				a = temp;
				Assert::AreEqual(size_t(1), a.Size());
				Assert::AreEqual(size_t(1), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Matrix, a.Type());
			}

			{
				Datum a;
				Foo b;
				RTTI* c = &b;
				a = c;
				Assert::AreEqual(size_t(1), a.Size());
				Assert::AreEqual(size_t(1), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Pointer, a.Type());
			}

			{
				Datum a;
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.PushBackInt(10);
				a.PushBackInt(20);
				a.PushBackInt(30);
				a.PushBackInt(40);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(a.Type(), Datum::DatumTypes::Integer);
				Datum b;
				Assert::ExpectException<std::runtime_error>([&a, &b] {a = b; });
				b.PushBackString(s3);
				b.PushBackString(s4);
				Assert::AreEqual(size_t(2), b.Size());
				Assert::AreEqual(size_t(2), b.Capacity());
				Assert::AreEqual(b.Type(), Datum::DatumTypes::String);
				a = b;
				Assert::AreEqual(size_t(2), a.Size());
				Assert::AreEqual(size_t(2), a.Capacity());
				Assert::AreEqual(a.Type(), b.Type());
				Assert::AreEqual(a.Type(), Datum::DatumTypes::String);
			}

			{
				Datum a;
				a.SetStorageFloat(bits, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Float, a.Type());
				Assert::IsTrue(a.isExternal());
				Datum b;
				b.PushBackString(s4);
				Assert::IsFalse(b.isExternal());
				Assert::AreEqual(size_t(1), b.Size());
				Assert::AreEqual(size_t(1), b.Capacity());
				b = a;
				Assert::AreEqual(size_t(4), b.Size());
				Assert::AreEqual(size_t(4), b.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Float, b.Type());
				Assert::IsTrue(b.isExternal());
			}

			{
				Datum a;
				a.SetStorageInt(boats, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
				Assert::IsTrue(a.isExternal());
				Datum b;
				b.PushBackFloat(5.6f);
				Assert::IsFalse(b.isExternal());
				Assert::AreEqual(size_t(1), b.Size());
				Assert::AreEqual(size_t(1), b.Capacity());
				b = a;
				Assert::AreEqual(size_t(4), b.Size());
				Assert::AreEqual(size_t(4), b.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, b.Type());
				Assert::IsTrue(b.isExternal());
			}

			{
				Datum a;
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.PushBackFloat(2.5f);
				a.PushBackFloat(2.8f);
				a.PushBackFloat(2.89996f);;
				Assert::AreEqual(size_t(3), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Float, a.Type());
				Datum b;
				b.PushBackVector(s1);
				b.PushBackVector(s2);
				a = b;
				Assert::AreEqual(a.Size(), b.Size());
				Assert::AreEqual(a.Size(), b.Capacity());
				Assert::AreEqual(a.Type(), b.Type());
				Assert::AreEqual(Datum::DatumTypes::Vector, a.Type());
			}

			{
				Datum a;
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.PushBackFloat(2.5f);
				a.PushBackFloat(2.8f);
				a.PushBackFloat(2.89996f);;
				Assert::AreEqual(size_t(3), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Float, a.Type());
				Datum b;
				b=a;
				Assert::AreEqual(a.Size(), b.Size());
				Assert::AreEqual(a.Size(), b.Capacity());
				Assert::AreEqual(a.Type(), b.Type());
				Assert::AreEqual(Datum::DatumTypes::Float, a.Type());
			}
		}

		TEST_METHOD(SetType)
		{
			Datum a;
			Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
			a.SetType(Datum::DatumTypes::Integer);
			Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
			Assert::ExpectException<std::runtime_error>([&a] {a.SetType(Datum::DatumTypes::Float); });
		}

		TEST_METHOD(MoveSemantics)
		{
			const string s3 = "Brian";
			const string s4 = "Stewie";

			{
				Datum a;
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.PushBackInt(10);
				a.PushBackInt(20);
				a.PushBackInt(30);
				a.PushBackInt(40);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
				Datum b(std::move(a));
				Assert::AreEqual(size_t(4), b.Size());
				Assert::AreEqual(size_t(4), b.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, b.Type());
			}

			{
				Datum a;
				Assert::AreEqual(Datum::DatumTypes::Unknown, a.Type());
				a.PushBackInt(10);
				a.PushBackInt(20);
				a.PushBackInt(30);
				a.PushBackInt(40);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
				Datum b;
				b.PushBackString(s3);
				b.PushBackString(s4);
				Assert::AreEqual(size_t(2), b.Size());
				Assert::AreEqual(size_t(2), b.Capacity());
				Assert::AreEqual(Datum::DatumTypes::String, b.Type());
				b = std::move(a);
				Assert::AreEqual(size_t(4), b.Size());
				Assert::AreEqual(size_t(4), b.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, b.Type());
			}
		}

		TEST_METHOD(EquivalenceOperators)
		{
			const string s3 = "Brian";
			const string s4 = "Stewie";
			const string s5 = "Lois";
			int boats[]{ 1,2,3,4 };
			Foo g(100);
			Foo h(200);
			{
				Datum a;
				a = 10;
				Assert::IsTrue(a == 10);
				Assert::IsFalse(a != 10);
				Assert::IsTrue(a != 200);
			}

			{
				Datum a;
				a = 10.5f;
				Assert::IsTrue(a == 10.5f);
				Assert::IsFalse(a != 10.5f);
				Assert::IsTrue(a != 100.56f);
			}

			{
				Datum a;
				a = s3;
				Assert::IsTrue(a == s3);
				Assert::IsFalse(a != s3);
				Assert::IsTrue(a != "Joe");
			}

			{
				Datum a;
				glm::vec4 temp;
				a = temp;
				Assert::IsTrue(a == temp);
				Assert::IsFalse(a != temp);
				Assert::IsTrue(a != glm::vec4(1,2,3,4));
			}

			{
				Datum a;
				glm::mat4 temp;
				a = temp;
				Assert::IsTrue(a == temp);
				Assert::IsFalse(a != temp);
				Assert::IsTrue(a != glm::mat4(1, 2, 3, 4,1,1,1,1,1,1,11,1,1,1,1,1));
			}

			{
				Datum a;
				Foo b;
				a = &b;
				Assert::IsTrue(a == &b);
				Assert::IsFalse(a != &b);
			}

			{
				Datum a;
				RTTI* b = &g;
				RTTI* c = &h;
				RTTI* k = &h;
				RTTI* l = &g;
				a.PushBackPointer(b);
				a.PushBackPointer(c);
				Datum d(a);
				Assert::IsTrue(a == d);
				Assert::IsFalse(a != d);
				d.PopBack();
				Assert::IsTrue(a != d);
				Assert::IsFalse(a == d);
				d.PopBack();
				d.PushBackPointer(k);
				d.PushBackPointer(l);
				Assert::IsTrue(a != d);
				Assert::IsFalse(a == d);
				Assert::IsTrue(a != l);
			}



			{
				Datum a;
				a.PushBackString(s3);
				a.PushBackString(s4);
				Assert::AreEqual(size_t(2), a.Size());
				Assert::AreEqual(size_t(2), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::String, a.Type());
				Datum b(a);
				Assert::AreEqual(size_t(2), b.Size());
				Assert::AreEqual(size_t(2), b.Capacity());
				Assert::AreEqual(Datum::DatumTypes::String, b.Type());
				Assert::IsFalse(a.isExternal());
				Assert::IsFalse(b.isExternal());
				Assert::IsTrue(a == b);
				Assert::IsFalse(a != b);
				Assert::AreEqual(s3, a.FrontString());
				Assert::AreEqual(s3, b.FrontString());
				Assert::AreEqual(s4, a.BackString());
				Assert::AreEqual(s4, b.BackString());
				b.PopBack();
				b.PushBackString(s5);
				Assert::IsFalse(a == b);
				Assert::IsTrue(a != b);
			}

			{
				Datum a;
				a.PushBackInt(10);
				a.PushBackInt(20);
				a.PushBackInt(30);
				a.PushBackInt(40);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
				Datum b(a);
				Assert::AreEqual(size_t(4), b.Size());
				Assert::AreEqual(size_t(4), b.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, b.Type());
				Assert::IsFalse(a.isExternal());
				Assert::IsFalse(b.isExternal());
				Assert::IsTrue(a == b);
				Assert::IsFalse(a != b);
				Assert::AreEqual(10, a.FrontInt());
				Assert::AreEqual(10, b.FrontInt());
				Assert::AreEqual(40, a.BackInt());
				Assert::AreEqual(40, b.BackInt());
			}

			{
				Datum a;
				a.SetStorageInt(boats, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
				Datum b(a);
				Assert::AreEqual(size_t(4), b.Size());
				Assert::AreEqual(size_t(4), b.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, b.Type());
				Assert::IsTrue(a.isExternal());
				Assert::IsTrue(b.isExternal());
				Assert::IsTrue(a == b);
				Assert::IsFalse(a != b);
				Assert::AreEqual(1, a.FrontInt());
				Assert::AreEqual(1, b.FrontInt());
				Assert::AreEqual(4, a.BackInt());
				Assert::AreEqual(4, b.BackInt());
				
			}
		}

		TEST_METHOD(Resize)
		{
			const string s3 = "Brian";
			const string s4 = "Stewie";
			const string s5 = "Lois";
			int boats[]{ 1,2,3,4 };
			
			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a] {a.Resize(10); });
				a.SetStorageInt(boats, 4);
				Assert::ExpectException<std::runtime_error>([&a] {a.Resize(10); });

				Datum b;
				b.PushBackInt(10);
				b.PushBackInt(20);
				b.PushBackInt(30);
				Assert::AreEqual(size_t(3), b.Size());
				Assert::AreEqual(size_t(3), b.Capacity());
				b.Resize(0);
				Assert::AreEqual(size_t(0), b.Size());
				Assert::AreEqual(size_t(0), b.Capacity());
				
			}

			{
				Datum a;
				a.PushBackString(s3);
				a.PushBackString(s4);
				a.PushBackString(s5);
				Assert::AreEqual(size_t(3), a.Size());
				Assert::AreEqual(size_t(3), a.Capacity());
				a.Clear();
				Assert::AreEqual(size_t(0), a.Size());
				Assert::AreEqual(size_t(3), a.Capacity());
			}
		}

		TEST_METHOD(SetStorage)
		{
			string s3[]{"Brian", "Stewie", "Lois"};
			Foo g, h, i, j;
			int boats[]{ 1,2,3,4 };
			float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
			glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
			glm::mat4 s2[]{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

			{
				Datum a;
				int* arrayNull = nullptr;
				Assert::ExpectException<std::runtime_error>([&a, &arrayNull] {a.SetStorageInt(arrayNull, 5); });
				a.SetStorageInt(boats, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Integer, a.Type());
				Assert::IsTrue(a.isExternal());
			}

			{
				Datum a;
				float* arrayNull = nullptr;
				Assert::ExpectException<std::runtime_error>([&a, &arrayNull] {a.SetStorageFloat(arrayNull, 5); });
				a.SetStorageFloat(bits, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Float, a.Type());
				Assert::IsTrue(a.isExternal());
			}

			{
				Datum a;
				std::string* arrayNull = nullptr;
				Assert::ExpectException<std::runtime_error>([&a, &arrayNull] {a.SetStorageString(arrayNull, 5); });
				a.SetStorageString(s3, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::String, a.Type());
				Assert::IsTrue(a.isExternal());
			}

			{
				Datum a;
				glm::vec4* arrayNull = nullptr;
				Assert::ExpectException<std::runtime_error>([&a, &arrayNull] {a.SetStorageVector(arrayNull, 5); });
				a.SetStorageVector(s1, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Vector, a.Type());
				Assert::IsTrue(a.isExternal());
			}

			{
				Datum a;
				glm::mat4* arrayNull = nullptr;
				Assert::ExpectException<std::runtime_error>([&a, &arrayNull] {a.SetStorageMatrix(arrayNull, 5); });
				a.SetStorageMatrix(s2, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Matrix, a.Type());
				Assert::IsTrue(a.isExternal());
			}

			{
				Datum a;
				RTTI** arrayNull = nullptr;
				RTTI* rtts[]{ &g, &h, &i, &j };
				Assert::ExpectException<std::runtime_error>([&a, &arrayNull] {a.SetStoragePointer(arrayNull, 5); });
				a.SetStoragePointer(rtts, 4);
				Assert::AreEqual(size_t(4), a.Size());
				Assert::AreEqual(size_t(4), a.Capacity());
				Assert::AreEqual(Datum::DatumTypes::Pointer, a.Type());
				Assert::IsTrue(a.isExternal());
			}
		}

		TEST_METHOD(Set)
		{
			string s3[]{ "Brian", "Stewie", "Lois" };
			Foo g, h, i;
			int boats[]{ 1,2,3,4 };
			float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
			glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
			glm::mat4 s2[]{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

			{
				Datum a;
				a.PushBackInt(1);
				Assert::ExpectException<std::runtime_error>([&a] {a.SetInt(10,5); });
				a.SetInt(25, 0);
				Assert::AreEqual(25, a.FrontInt());
			}

			{
				Datum a;
				a.PushBackFloat(2.56f);
				Assert::ExpectException<std::runtime_error>([&a] {a.SetFloat(10.56f, 5); });
				a.SetFloat(25.6f, 0);
				Assert::AreEqual(25.6f, a.FrontFloat());
			}
			
			{
				Datum a;
				a.PushBackString("Peter"s);
				Assert::ExpectException<std::runtime_error>([&a] {a.SetString("Meg", 5); });
				a.SetString("Meg"s, 0);
				Assert::AreEqual("Meg"s, a.FrontString());
			}

			{
				Datum a;
				a.PushBackVector(s1[0]);
				Assert::ExpectException<std::runtime_error>([&a, &s1] {a.SetVector(s1[1], 5); });
				a.SetVector(s1[1], 0);
				Assert::AreEqual(s1[1], a.FrontVector());
			}

			{
				Datum a;
				a.PushBackMatrix(s2[0]);
				Assert::ExpectException<std::runtime_error>([&a, &s2] {a.SetMatrix(s2[1], 5); });
				a.SetMatrix(s2[1], 0);
				Assert::AreEqual(s2[1], a.FrontMatrix());
			}

			{
				Datum a;
				RTTI* b = &g;
				RTTI* c = &h;
				a.PushBackPointer(b);
				Assert::ExpectException<std::runtime_error>([&a, &c] {a.SetPointer(c, 5); });
				a.SetPointer(c, 0);
				Assert::AreEqual(c, a.FrontPointer());
			}
		}

		TEST_METHOD(Get)
		{
			string s3[]{ "Brian", "Stewie", "Lois" };
			int boats[]{ 1,2,3,4 };
			float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
			glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
			glm::mat4 s2[]{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a] {a.GetInt(0); });
				a.PushBackInt(1);
				Assert::ExpectException<std::runtime_error>([&a] {a.GetInt(1); });
				Assert::AreEqual(1, a.GetInt());
			}

			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a] {a.GetFloat(0); });
				a.PushBackFloat(10.5f);
				Assert::ExpectException<std::runtime_error>([&a] {a.GetFloat(1); });
				Assert::AreEqual(10.5f, a.GetFloat());
			}

			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a] {a.GetString(0); });
				a.PushBackString("Peter"s);
				Assert::ExpectException<std::runtime_error>([&a] {a.GetString( 1); });
				Assert::AreEqual("Peter"s, a.GetString());
			}

			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a, &s1] {a.GetVector(0); });
				a.PushBackVector(s1[0]);
				Assert::ExpectException<std::runtime_error>([&a, &s1] {a.GetVector(1); });
				a.GetVector(0);
				Assert::AreEqual(s1[0], a.GetVector());
			}

			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a, &s2] {a.GetMatrix(0); });

				a.PushBackMatrix(s2[0]);
				Assert::ExpectException<std::runtime_error>([&a, &s2] {a.GetMatrix(1); });
				Assert::AreEqual(s2[0], a.GetMatrix());
			}

			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a] {a.GetPointer(0); });
				Foo g;
				RTTI* b = &g;
				a.PushBackPointer(b);
				Assert::ExpectException<std::runtime_error>([&a] {a.GetPointer(1); });
				Assert::AreEqual(b, a.GetPointer());
			}
		}

		TEST_METHOD(SetFromString)
		{
			string s3[]{ "Brian", "Stewie", "Lois" };
			int boats[]{ 1,2,3,4 };
			float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
			glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
			glm::mat4 s2[]{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
			glm::mat4 test{ 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8 };
			
			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a] {a.SetFromString( "25"s); });

			}
			{
				Datum a;
				a.PushBackInt(1);
				a.SetFromString("25"s);
				Assert::AreEqual(25, a.FrontInt());
			}

			{
				Datum a;
				a.PushBackFloat(2.56f);
				a.SetFromString("25.6f"s);
				Assert::AreEqual(25.6f, a.FrontFloat());
			}

			{
				Datum a;
				a.PushBackString("Peter"s);
				a.SetFromString("Meg"s);
				Assert::AreEqual("Meg"s, a.FrontString());
			}

			{
				Datum a;
				a.PushBackVector(s1[0]);
				a.SetFromString("vec4(1, 2, 3, 4)"s);
				Assert::AreEqual(glm::vec4(1, 2, 3, 4), a.FrontVector());
			}

			{
				Datum a;
				a.PushBackMatrix(s2[0]);
				a.SetFromString("mat4((1,2,3,4),(5,6,7,8),(1,2,3,4),(5,6,7,8))");
				Assert::AreEqual(test, a.FrontMatrix());
			}

			{
				Datum a;
				Foo b;
				RTTI* c = &b;
				Assert::ExpectException<std::runtime_error>([&a] {a.SetFromString("5"s); });
				a.PushBackPointer(c);
				Assert::AreEqual(Datum::DatumTypes::Pointer, a.Type());
				Assert::ExpectException<std::runtime_error>([&a] {a.SetFromString("5"s); });

			}
		}

		TEST_METHOD(ToString)
		{
			glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
			glm::mat4 test{ 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8 };

			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a] {a.ToString(size_t(57)); });

			}
			{
				Datum a;
				a.PushBackInt(256);
				a.PushBackInt(652);
				Assert::AreEqual("256"s, a.ToString(size_t(0)));
				Assert::AreEqual("652"s, a.ToString(size_t(1)));
			}

			{
				Datum a;
				a.PushBackFloat(2.56f);
				Assert::AreEqual("2.560000"s, a.ToString(0));
			}

			{
				Datum a;
				a.PushBackString("Peter"s);
				Assert::AreEqual("Peter"s, a.ToString());
			}

			{
				Datum a;
				a.PushBackVector(s1[0]);
				Assert::AreEqual("vec4(10.000000, 20.000000, 30.000000, 40.000000)"s, a.ToString());
			}

			{
				Datum a;
				a.PushBackMatrix(test);
				Assert::AreEqual("mat4((1.000000, 2.000000, 3.000000, 4.000000), (5.000000, 6.000000, 7.000000, 8.000000), (1.000000, 2.000000, 3.000000, 4.000000), (5.000000, 6.000000, 7.000000, 8.000000))"s, a.ToString());
			}

			{
				Datum a;
				Foo b;
				RTTI* c = &b;
				RTTI* cNull = nullptr;
				a.PushBackPointer(cNull);
				Assert::AreEqual("nullptr"s, a.ToString());
				a.PopBack();
				a.PushBackPointer(c);
				Assert::AreEqual("RTTI"s, a.ToString());

			}
		}
		TEST_METHOD(PushBack)
		{
			glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
			glm::mat4 test{ 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8 };
			Foo p;
			RTTI* m = &p;

			{
				Datum a;
				a.PushBackFloat(2.5f);
				Assert::ExpectException<std::runtime_error>([&a] {a.PushBackInt(25); });
				Assert::ExpectException<std::runtime_error>([&a] {a.PushBackString("Hello"); });
				Assert::ExpectException<std::runtime_error>([&a, &s1] {a.PushBackVector(s1[0]); });
				Assert::ExpectException<std::runtime_error>([&a, &test] {a.PushBackMatrix(test); });
				Assert::ExpectException<std::runtime_error>([&a, &m] {a.PushBackPointer(m); });

			}

			{
				Datum a;
				a.PushBackInt(2);
				Assert::ExpectException<std::runtime_error>([&a] {a.PushBackFloat(25.5f); });
			}
		}
		TEST_METHOD(Front)
		{
			{
				string s3[]{ "Brian", "Stewie", "Lois" };
				int boats[]{ 1,2,3,4 };
				float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
				glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
				glm::mat4 s2[]{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
				Foo u;
				Foo x;
				RTTI* y = &u;
				RTTI* z = &x;
				{
					Datum a;
					a.SetType(Datum::DatumTypes::Integer);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontInt(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontFloat(); });
					a.PushBackInt(1);
					Assert::ExpectException<std::runtime_error>([&a] {a.SetInt(10, 5); });
					a.SetInt(25, 0);
					Assert::AreEqual(25, a.FrontInt());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::Float);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontFloat(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontInt(); });

					a.PushBackFloat(2.56f);
					Assert::ExpectException<std::runtime_error>([&a] {a.SetFloat(10.56f, 5); });
					a.SetFloat(25.6f, 0);
					Assert::AreEqual(25.6f, a.FrontFloat());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::String);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontString(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontVector(); });
					a.PushBackString("Peter"s);
					Assert::ExpectException<std::runtime_error>([&a] {a.SetString("Meg", 5); });
					a.SetString("Meg"s, 0);
					Assert::AreEqual("Meg"s, a.FrontString());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::Vector);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontMatrix(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontVector(); });
					a.PushBackVector(s1[0]);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontString(); });
					Assert::ExpectException<std::runtime_error>([&a, &s1] {a.SetVector(s1[1], 5); });
					a.SetVector(s1[1], 0);
					Assert::AreEqual(s1[1], a.FrontVector());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::Matrix);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontMatrix(); });
					a.PushBackMatrix(s2[0]);
					Assert::ExpectException<std::runtime_error>([&a, &s2] {a.SetMatrix(s2[1], 5); });
					a.SetMatrix(s2[1], 0);
					Assert::AreEqual(s2[1], a.FrontMatrix());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::Integer);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontInt(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontFloat(); });
					const Datum b(a);
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontInt(); });
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontFloat(); });
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontVector(); });
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontString(); });
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontMatrix(); });


					a.PushBackInt(1);
					Assert::ExpectException<std::runtime_error>([&a] {a.SetInt(10, 5); });
					a.SetInt(25, 0);
					Assert::AreEqual(25, a.FrontInt());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::Float);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontFloat(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontInt(); });
					const Datum b(a);
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontInt(); });
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontFloat(); });



					a.PushBackFloat(2.56f);
					Assert::ExpectException<std::runtime_error>([&a] {a.SetFloat(10.56f, 5); });
					a.SetFloat(25.6f, 0);
					Assert::AreEqual(25.6f, a.FrontFloat());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::String);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontString(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontVector(); });

					const Datum b(a);
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontString(); });

					a.PushBackString("Peter"s);
					Assert::ExpectException<std::runtime_error>([&a] {a.SetString("Meg", 5); });
					a.SetString("Meg"s, 0);
					Assert::AreEqual("Meg"s, a.FrontString());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::Vector);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontMatrix(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontVector(); });
					const Datum b(a);
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontVector(); });


					a.PushBackVector(s1[0]);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontString(); });
					Assert::ExpectException<std::runtime_error>([&a, &s1] {a.SetVector(s1[1], 5); });
					a.SetVector(s1[1], 0);
					Assert::AreEqual(s1[1], a.FrontVector());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::Matrix);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontMatrix(); });
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontPointer(); });

					const Datum b(a);
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontMatrix(); });
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontPointer(); });

					a.PushBackMatrix(s2[0]);
					Assert::ExpectException<std::runtime_error>([&a, &s2] {a.SetMatrix(s2[1], 5); });
					a.SetMatrix(s2[1], 0);
					Assert::AreEqual(s2[1], a.FrontMatrix());
				}

				{
					Datum a;
					a.SetType(Datum::DatumTypes::Pointer);
					Assert::ExpectException<std::runtime_error>([&a] {a.FrontPointer(); });

					const Datum b(a);
					Assert::ExpectException<std::runtime_error>([&b] {b.FrontPointer(); });

					a.PushBackPointer(y);
					Assert::ExpectException<std::runtime_error>([&a, &z] {a.SetPointer(z, 3); });
					a.SetPointer(z, 0);
					Assert::AreEqual(z, a.FrontPointer());
				}
			}
		}
		TEST_METHOD(Back)
		{
				{
					string s3[]{ "Brian", "Stewie", "Lois" };
					int boats[]{ 1,2,3,4 };
					float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
					glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
					glm::mat4 s2[]{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
			
					{
						Datum a;
						a.SetType(Datum::DatumTypes::Integer);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackInt(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackFloat(); });
						a.PushBackInt(1);
						Assert::ExpectException<std::runtime_error>([&a] {a.SetInt(10, 5); });
						a.SetInt(25, 0);
						Assert::AreEqual(25, a.BackInt());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::Float);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackFloat(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackInt(); });

						a.PushBackFloat(2.56f);
						Assert::ExpectException<std::runtime_error>([&a] {a.SetFloat(10.56f, 5); });
						a.SetFloat(25.6f, 0);
						Assert::AreEqual(25.6f, a.BackFloat());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::String);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackString(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackVector(); });
						a.PushBackString("Peter"s);
						Assert::ExpectException<std::runtime_error>([&a] {a.SetString("Meg", 5); });
						a.SetString("Meg"s, 0);
						Assert::AreEqual("Meg"s, a.BackString());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::Vector);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackMatrix(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackVector(); });
						a.PushBackVector(s1[0]);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackString(); });
						Assert::ExpectException<std::runtime_error>([&a, &s1] {a.SetVector(s1[1], 5); });
						a.SetVector(s1[1], 0);
						Assert::AreEqual(s1[1], a.BackVector());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::Matrix);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackMatrix(); });
						a.PushBackMatrix(s2[0]);
						Assert::ExpectException<std::runtime_error>([&a, &s2] {a.SetMatrix(s2[1], 5); });
						a.SetMatrix(s2[1], 0);
						Assert::AreEqual(s2[1], a.BackMatrix());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::Integer);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackInt(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackFloat(); });
						const Datum b(a);
						Assert::ExpectException<std::runtime_error>([&b] {b.BackInt(); });
						Assert::ExpectException<std::runtime_error>([&b] {b.BackFloat(); });
						Assert::ExpectException<std::runtime_error>([&b] {b.BackVector(); });
						Assert::ExpectException<std::runtime_error>([&b] {b.BackString(); });
						Assert::ExpectException<std::runtime_error>([&b] {b.BackMatrix(); });


						a.PushBackInt(1);
						Assert::ExpectException<std::runtime_error>([&a] {a.SetInt(10, 5); });
						a.SetInt(25, 0);
						Assert::AreEqual(25, a.BackInt());
						const Datum c(a);
						Assert::AreEqual(25, c.BackInt());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::Float);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackFloat(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackInt(); });
						const Datum b(a);
						Assert::ExpectException<std::runtime_error>([&b] {b.BackInt(); });
						Assert::ExpectException<std::runtime_error>([&b] {b.BackFloat(); });



						a.PushBackFloat(2.56f);
						Assert::ExpectException<std::runtime_error>([&a] {a.SetFloat(10.56f, 5); });
						a.SetFloat(25.6f, 0);
						Assert::AreEqual(25.6f, a.BackFloat());
						const Datum c(a);
						Assert::AreEqual(25.6f, c.BackFloat());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::String);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackString(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackVector(); });

						const Datum b(a);
						Assert::ExpectException<std::runtime_error>([&b] {b.BackString(); });

						a.PushBackString("Peter"s);
						Assert::ExpectException<std::runtime_error>([&a] {a.SetString("Meg", 5); });
						a.SetString("Meg"s, 0);
						Assert::AreEqual("Meg"s, a.BackString());
						const Datum c(a);
						Assert::AreEqual("Meg"s, c.BackString());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::Vector);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackMatrix(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackVector(); });
						const Datum b(a);
						Assert::ExpectException<std::runtime_error>([&b] {b.BackVector(); });


						a.PushBackVector(s1[0]);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackString(); });
						Assert::ExpectException<std::runtime_error>([&a, &s1] {a.SetVector(s1[1], 5); });
						a.SetVector(s1[1], 0);
						Assert::AreEqual(s1[1], a.BackVector());
						const Datum c(a);
						Assert::AreEqual(s1[1], c.BackVector());
					}

					{
						Datum a;
						a.SetType(Datum::DatumTypes::Matrix);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackMatrix(); });
						Assert::ExpectException<std::runtime_error>([&a] {a.BackPointer(); });

						const Datum b(a);
						Assert::ExpectException<std::runtime_error>([&b] {b.BackMatrix(); });
						Assert::ExpectException<std::runtime_error>([&b] {b.BackPointer(); });

						a.PushBackMatrix(s2[0]);
						Assert::ExpectException<std::runtime_error>([&a, &s2] {a.SetMatrix(s2[1], 5); });
						a.SetMatrix(s2[1], 0);
						Assert::AreEqual(s2[1], a.BackMatrix());
						const Datum c(a);
						Assert::AreEqual(s2[1], c.BackMatrix());
					}

					{
						Foo u;
						Foo x;
						Datum a;
						a.SetType(Datum::DatumTypes::Pointer);
						Assert::ExpectException<std::runtime_error>([&a] {a.BackPointer(); });

						const Datum b(a);
						Assert::ExpectException<std::runtime_error>([&b] {b.BackPointer(); });
						Foo t;
						RTTI* e = &t;
						const RTTI* q = e;
						a.PushBackPointer(e);
						Assert::AreEqual(e, a.BackPointer());
						const Datum k = a;
						Assert::AreEqual(q, k.BackPointer());
					}
				}
		}
		TEST_METHOD(Find)
		{
			string s3[]{ "Brian", "Stewie", "Lois" };
			int boats[]{ 1,2,3,4 };
			float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
			glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
			glm::mat4 s2[]{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
			Foo g;
			RTTI* h = &g;
			{
				Datum a;
				Assert::ExpectException<std::runtime_error>([&a] {a.FindInt(125); });
				Assert::ExpectException<std::runtime_error>([&a] {a.FindFloat(125.56f); });
				Assert::ExpectException<std::runtime_error>([&a] {a.FindString("Meg"s); });
				Assert::ExpectException<std::runtime_error>([&a, &s1] {a.FindVector(s1[0]); });
				Assert::ExpectException<std::runtime_error>([&a, &s2] {a.FindMatrix(s2[0]); });
				Assert::ExpectException<std::runtime_error>([&a, &h] {a.FindPointer(h); });
			}
		}
		TEST_METHOD(Remove)
		{
			{
				string s3[]{ "Brian", "Stewie", "Lois" };
				int boats[]{ 1,2,3,4 };
				float bits[]{ 1.256f, 5.645f, 8.9f, 88.6f };
				glm::vec4 s1[]{ {10, 20,30,40},{ 1, 2,3,4 } };
				glm::mat4 s2[]{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, {4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
				Foo r;
				RTTI* l = &r;
				{
					Datum a;
					a.PushBackInt(100);
					a.PushBackInt(200);
					a.PushBackInt(300);
					Assert::ExpectException<std::runtime_error>([&a] {a.RemoveFloat(100.0f); });
					Assert::ExpectException<std::runtime_error>([&a, &l] {a.RemovePointer(l); });
					Assert::IsTrue(a.RemoveInt(100));
					Assert::IsFalse(a.RemoveInt(100));
					Assert::AreEqual(size_t(2), a.Size()); 
				}

				{
					Datum a;
					a.PushBackFloat(100.26f);
					a.PushBackFloat(200.25f);
					a.PushBackFloat(300.14f);
					Assert::ExpectException<std::runtime_error>([&a] {a.RemoveInt(100); });
					Assert::IsTrue(a.RemoveFloat(100.26f));
					Assert::IsFalse(a.RemoveFloat(100.26f));
					Assert::AreEqual(size_t(2), a.Size());
				}

				{
					Datum a;
					a.PushBackString(s3[0]);
					a.PushBackString(s3[1]);
					a.PushBackString(s3[2]);
					Assert::ExpectException<std::runtime_error>([&a, &s2] {a.RemoveMatrix(s2[0]); });
					Assert::ExpectException<std::runtime_error>([&a, &s1] {a.RemoveVector(s1[0]); });
					Assert::IsTrue(a.RemoveString(s3[1]));
					Assert::IsFalse(a.RemoveString(s3[1]));
					Assert::AreEqual(size_t(2), a.Size());
				}

				{
					Datum a;
					a.PushBackVector(s1[0]);
					a.PushBackVector(s1[1]);
					Assert::IsTrue(a.RemoveVector(s1[1]));
					Assert::IsFalse(a.RemoveVector(s1[1]));
					Assert::AreEqual(size_t(1), a.Size());
				}

				{
					Datum a;
					Assert::ExpectException<std::runtime_error>([&a] {a.RemoveAt(0); });

					a.PushBackMatrix(s2[0]);
					a.PushBackMatrix(s2[1]);
					a.PushBackMatrix(s2[2]);
					a.PushBackMatrix(s2[3]);
					Assert::ExpectException<std::runtime_error>([&a] {a.RemoveString("Chris"s); });
					Assert::IsTrue(a.RemoveMatrix(s2[2]));
					Assert::IsFalse(a.RemoveMatrix(s2[2]));
					Assert::AreEqual(size_t(3), a.Size());
				}

				{
					Datum a;
					a.SetStorageInt(boats, 5);
					Assert::ExpectException<std::runtime_error>([&a] {a.RemoveAt(0); });
				}

				{
					Foo u;
					Foo x;
					Foo t;
					RTTI* d = &u;
					RTTI* e = &x;
					RTTI* j = &t;
					Datum a;
					Assert::ExpectException<std::runtime_error>([&a, &d] {a.RemoveAt(0); });
					a.PushBackPointer(d);
					a.PushBackPointer(e);
					Assert::IsFalse(a.RemovePointer(j));
					Assert::IsTrue(a.RemovePointer(d));
					Assert::AreEqual(size_t(1), a.Size());


				}
			}
		}



	private:
		inline static _CrtMemState _startMemState;
	};
}