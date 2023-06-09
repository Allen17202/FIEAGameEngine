#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "HashMap.h"
#include "SList.h"
#include "Vector.h"
#include "ToStringSpecializations.h"
#include "DefaultEquality.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;



namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<HashMap<Foo, int>::Iterator>(const HashMap<Foo, int>::Iterator& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<HashMap<Foo, int>::Iterator>(const HashMap<Foo, int>::Iterator* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<HashMap<Foo, int>::Iterator>(HashMap<Foo, int>::Iterator* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<HashMap<Foo, int>::ConstIterator>(const HashMap<Foo, int>::ConstIterator& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<HashMap<Foo, int>::ConstIterator>(const HashMap<Foo, int>::ConstIterator* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<HashMap<Foo, int>::ConstIterator>(HashMap<Foo, int>::ConstIterator* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::Iterator>(const HashMap<int, Foo>::Iterator& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::Iterator>(const HashMap<int, Foo>::Iterator* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::Iterator>(HashMap<int, Foo>::Iterator* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::ConstIterator>(const HashMap<int, Foo>::ConstIterator& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::ConstIterator>(const HashMap<int, Foo>::ConstIterator* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::ConstIterator>(HashMap<int, Foo>::ConstIterator* t)
	{
		RETURN_WIDE_STRING(t);
	}
}
namespace LibraryDesktopTests
{
	TEST_CLASS(HashMapTests)
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
				HashMap<Foo, int> map;
				Assert::AreEqual(size_t(2), map.Capacity());
				Assert::AreEqual(size_t(0), map.Size());
			}

			{
				HashMap<Foo, int> map(0);
				Assert::AreEqual(size_t(2), map.Capacity());
				Assert::AreEqual(size_t(0), map.Size());
			}

			{
				HashMap<Foo, int> map(15);
				Assert::AreEqual(size_t(15), map.Capacity());
				Assert::AreEqual(size_t(0), map.Size());
			}
		}

		TEST_METHOD(InitializerList)
		{
			HashMap<Foo, int> map =
			{
				std::pair<Foo, int> (Foo(10),100),
				std::pair<Foo, int> (Foo(20),200),
				std::pair<Foo, int> (Foo(30),300)
			};

			HashMap<std::string, int> mapString =
			{
				std::pair<const std::string, int>("Hi",100),
				std::pair<const std::string, int>("Hello",100),
				std::pair<const std::string, int>("Goodbye",100),
			};

			{
				Assert::AreEqual(size_t(3), map.Size());
				Assert::AreEqual(size_t(3), map.Capacity());
			}
		}

		
		TEST_METHOD(Dereference)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };

			std::pair<Foo, int> pair1 = std::make_pair(Foo(1), 1);
			std::pair<Foo, int> pair2 = std::make_pair(Foo(2), 2);
			std::pair<Foo, int> pair3 = std::make_pair(Foo(3), 3);

			HashMap<int, int> map =
			{
				std::pair<int, int>(1,100),
				std::pair<int, int>(2,200),
				std::pair<int, int>(3,300)
			};

			HashMap<std::string, int> mapString =
			{
				std::pair<const std::string, int>("Hi",100),
				std::pair<const std::string, int>("Hello",100),
				std::pair<const std::string, int>("Goodbye",100),
			};

			{
				Assert::AreEqual(size_t(3), map.Size());
				Assert::AreEqual(size_t(3), map.Capacity());
				Assert::AreEqual(map.At(1), 100);
				Assert::AreEqual(map.At(2), 200);
				Assert::AreEqual(map.At(3), 300);
			}

			{
				Assert::AreEqual(size_t(3), mapString.Size());
				Assert::AreEqual(size_t(3), mapString.Capacity());
			}

			{
				HashMap<std::string, int>::Iterator it;
				Assert::ExpectException<std::runtime_error>([&it]() { it->first; });
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}
		}

		TEST_METHOD(At)
		{
			std::pair<Foo, int> pair1 = std::make_pair(Foo(1), 1);
			std::pair<Foo, int> pair2 = std::make_pair(Foo(2), 2);
			std::pair<Foo, int> pair3 = std::make_pair(Foo(3), 3);

			std::pair<int, Foo> d(100, Foo(1));
			std::pair<int, Foo> e(200, Foo(2));
			std::pair<int, Foo> f(300, Foo(3));

			std::pair<int, const Foo> g(100, Foo(1));
			std::pair<int, const Foo> h(200, Foo(2));
			std::pair<int, const Foo> i(300, Foo(3));
			std::pair<int, const Foo> j(300, Foo(3));

			{
				HashMap<Foo, int> map(20);
				Assert::ExpectException<std::runtime_error>([&map]() { map.At(Foo(10)); });
				const HashMap<Foo, int>& mapTwo = map;
				Assert::ExpectException<std::runtime_error>([&mapTwo]() { mapTwo.At(Foo(10)); });

			}


			{
				HashMap<int, Foo> map(20);
				map.Insert(d);
				map.Insert(e);
				map.Insert(f);
				Assert::AreEqual(map.At(d.first), d.second);
				Assert::AreEqual(map.At(e.first), e.second);
				Assert::AreEqual(map.At(f.first), f.second);
			}

			{
				HashMap<const int, const Foo> map(20);
				map.Insert(g);
				map.Insert(h);
				map.Insert(i);
				const HashMap<const int, const Foo>& listTwo = map;
				Assert::AreEqual(listTwo.At(g.first), g.second);
				Assert::AreEqual(listTwo.At(h.first), h.second);
				Assert::AreEqual(listTwo.At(i.first), i.second);
			}

			{
				HashMap<std::string, Foo> map(15);
				Assert::AreEqual(std::size_t(0), map.Size());
				std::pair<std::string, Foo> p1 = std::make_pair("Peter", Foo(1));
				std::pair<std::string, Foo> p2 = std::make_pair("Lois", Foo(2));
				std::pair<std::string, Foo> p3 = std::make_pair("Stewie", Foo(3));
				map.Insert(p1);
				map.Insert(p2);
				map.Insert(p3);

				Assert::AreEqual(p1.second, map.At(p1.first));
				Assert::AreEqual(p2.second, map.At(p2.first));
				Assert::AreEqual(p3.second, map.At(p3.first));
			}
		}

		TEST_METHOD(Insert)
		{
			std::pair<int, Foo> a(1, Foo(1));
			std::pair<int, Foo> b(2, Foo(2));
			std::pair<int, Foo> c(3, Foo(3));
			std::pair<int, Foo> d(4, Foo(4));

			{
				HashMap<int, Foo> list;
				list.Insert(a);
				Assert::AreEqual((*(list.begin())).second, a.second);
			}

			{
				HashMap<int, Foo> list(5);
				Assert::IsTrue(list.Insert(a).second);
				Assert::AreEqual((*(list.begin())).second,a.second);
				Assert::IsFalse(list.Insert(a).second);
				Assert::IsTrue(list.Insert(b).second);
				Assert::IsTrue(list.Insert(c).second);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::IsTrue(list.ContainsKey(a.first));
				Assert::IsTrue(list.ContainsKey(2));
				Assert::IsTrue(list.ContainsKey(3));
				Assert::IsFalse(list.ContainsKey(4));
			}
		}

		TEST_METHOD(Move)
		{
			std::pair<int, Foo> a(1, Foo(1));
			std::pair<int, Foo> b(2, Foo(2));
			std::pair<int, Foo> c(3, Foo(3));
			{
				HashMap<int, Foo> list(10);
				list.Insert(a);
				list.Insert(b);
				list.Insert(c);
				HashMap<int, Foo> listCopy(std::move(list));
				Assert::AreEqual(size_t(3), listCopy.Size());
				Assert::IsTrue(listCopy.ContainsKey(1));
				Assert::IsTrue(listCopy.ContainsKey(2));
				Assert::IsTrue(listCopy.ContainsKey(3));
			}
		}

		TEST_METHOD(Clear)
		{
			std::pair<int, Foo> a(1, Foo(1));
			std::pair<int, Foo> b(2, Foo(2));
			std::pair<int, Foo> c(3, Foo(3));
			{
				HashMap<int, Foo> list(10);
				list.Insert(a);
				list.Insert(b);
				list.Insert(c);
				list.Clear();
				Assert::AreEqual(size_t(0), list.Size());
				Assert::AreEqual(size_t(10), list.Capacity());
			}
		}

		TEST_METHOD(End)
		{
			{
				HashMap<int, Foo> list(10);
				Assert::ExpectException<std::runtime_error>([&list]() { *list.end(); });
				const HashMap<int, Foo>& listTwo = list;
				Assert::ExpectException<std::runtime_error>([&list]() { *list.cend(); });
				Assert::ExpectException<std::runtime_error>([&listTwo]() { *listTwo.end(); });
			}
		}

		TEST_METHOD(IncrementOperator)
		{
			std::pair<int, Foo> a(1, Foo(1));
			std::pair<int, Foo> b(2, Foo(2));
			std::pair<int, Foo> c(3, Foo(3));

			{
				HashMap<int, Foo> list(10);
				HashMap<int, Foo>::Iterator itInvalid;
				Assert::ExpectException<std::runtime_error>([&itInvalid]() { itInvalid++; });
				Assert::ExpectException<std::runtime_error>([&itInvalid]() { ++itInvalid; });
				HashMap<int, Foo>::ConstIterator constItInvalid;
				Assert::ExpectException<std::runtime_error>([&constItInvalid]() { constItInvalid++; });
				Assert::ExpectException<std::runtime_error>([&constItInvalid]() { ++constItInvalid; });
				list.Insert(a);
				list.Insert(b);
				list.Insert(c);
				HashMap<int, Foo>::Iterator it = list.begin();
				Assert::AreEqual(it->second,c.second);
				Assert::AreEqual(it++->second, a.second);
				Assert::AreEqual((++it)->second, b.second);

				const HashMap<int, Foo> listConst = list;
				HashMap<int, Foo>::ConstIterator itConst = listConst.begin();
				Assert::AreEqual(itConst->second, c.second);
				Assert::AreEqual(itConst++->second, a.second);
				Assert::AreEqual((++itConst)->second, b.second);

				Assert::AreEqual(++it, list.end());
				Assert::AreEqual(++itConst, listConst.end());
				Assert::ExpectException<std::runtime_error>([&it]() { ++it; });
				Assert::ExpectException<std::runtime_error>([&itConst]() { ++itConst; });
			
				HashMap<int, Foo>::Iterator itWrong = list.end();
				Assert::ExpectException<std::runtime_error>([&itWrong]() { itWrong++; });
			}

			{
				HashMap<int, Foo> list(10);
				HashMap<int, Foo>::Iterator itInvalid;
				HashMap<int, Foo>::ConstIterator constItInvalid;
				list.Insert(a);
				list.Insert(b);
				list.Insert(c);
				HashMap<int, Foo>::Iterator it = list.begin();
				HashMap<int, Foo>::ConstIterator itConst = it;
				Assert::AreEqual(itConst->second, c.second);
				Assert::AreEqual(itConst++->second, a.second);
				Assert::AreEqual((++itConst)->second, b.second);
			}
		}

		TEST_METHOD(Begin)
		{
			std::pair<int, Foo> a(1, Foo(1));
			std::pair<int, Foo> b(2, Foo(2));
			std::pair<int, Foo> c(3, Foo(3));

			{
				HashMap<int, Foo> list(10);
				Assert::AreEqual(list.begin(), list.end());
			}

			{
				HashMap<int, Foo> list(10);
				const HashMap<int, Foo>& listTwo = list;
				Assert::AreEqual(list.cbegin(), listTwo.begin());
			}

			{
				HashMap<int, Foo> list(10);
				list.Insert(a);
				list.Insert(b);
				list.Insert(c);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::IsTrue(list.ContainsKey(1));
				Assert::IsTrue(list.ContainsKey(2));
				Assert::IsTrue(list.ContainsKey(3));
				Assert::AreEqual(list.begin()->second, c.second);
				const HashMap<int, Foo>& listTwo = list;
				Assert::AreEqual(list.cbegin()->second, c.second);
				Assert::AreEqual(listTwo.cbegin()->second, c.second);

			}
		}

		TEST_METHOD(Remove)
		{
			std::pair<int, Foo> a(1, Foo(1));
			std::pair<int, Foo> b(2, Foo(2));
			std::pair<int, Foo> c(3, Foo(3));
			std::pair<int, Foo> d(4, Foo(4));

			{
				HashMap<int, Foo> list;
				list.Insert(a);
				Assert::AreEqual((*(list.begin())).second, a.second);
			}

			{
				HashMap<int, Foo> list(5);
				Assert::IsTrue(list.Insert(a).second);
				Assert::AreEqual((*(list.begin())).second, a.second);
				Assert::IsFalse(list.Insert(a).second);
				Assert::IsTrue(list.Insert(b).second);
				Assert::IsTrue(list.Insert(c).second);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::IsTrue(list.ContainsKey(a.first));
				Assert::IsTrue(list.ContainsKey(2));
				Assert::IsTrue(list.ContainsKey(3));
				Assert::IsFalse(list.ContainsKey(4));

				list.Remove(3);
				Assert::IsTrue(list.ContainsKey(3));
				Assert::AreEqual(size_t(3), list.Size());
			}
		}
	private:
		inline static _CrtMemState _startMemState;
	};
}