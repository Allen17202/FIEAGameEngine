#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.h"
#include "Foo.h"
#include "ToStringSpecializations.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(VectorTests)
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
			// Default Constructor for Vector
			Vector<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());
			Assert::AreEqual(size_t(0), list.Capacity());
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });

		}

		TEST_METHOD(InitializerList)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };
			{
				Vector<Foo> list = {a,b,c};
				Assert::AreEqual(a, list[0]);
				Assert::AreEqual(b, list[1]);
				Assert::AreEqual(c, list[2]);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
			}
		}

		TEST_METHOD(Move)
		{

			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };
			const Foo d{ 40 };
			const Foo e{ 50 };
			const Foo f{ 60 };

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);

				Vector<Foo> copyOfList(std::move(list));
				Assert::AreEqual(size_t(3), copyOfList.Size());
				Assert::AreEqual(a, copyOfList.Front());
				Assert::AreEqual(c, copyOfList.Back());
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);

				Vector<Foo> copyOfList;
				copyOfList = std::move(list);
				Assert::AreEqual(size_t(3), copyOfList.Size());
				Assert::AreEqual(a, copyOfList.Front());
				Assert::AreEqual(c, copyOfList.Back());
			}
		}

		TEST_METHOD(ArrayIndexOperators)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };
			const Foo d{ 40 };
			const Foo e{ 50 };
			const Foo f{ 60 };

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::AreEqual(a, list[0]);
				Assert::AreEqual(b, list[1]);
				Assert::AreEqual(c, list[2]);
				Assert::ExpectException<std::runtime_error>([&list] {list[4]; });

				const Vector<Foo>& constList = {d,e,f};
				Assert::AreEqual(d, constList[0]);
				Assert::AreEqual(e, constList[1]);
				Assert::AreEqual(f, constList[2]);
				Assert::ExpectException<std::runtime_error>([&constList] {constList[4]; });

			}

			{
				Vector<Foo> list;
				Assert::ExpectException<std::runtime_error>([&list] {list[0]; });
			}

			{
				const Vector<Foo> list;
				Assert::ExpectException<std::runtime_error>([&list] {list[0]; });
			}
		}

		TEST_METHOD(CopyConstructor)
		{

			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };
			const Foo d{ 40 };
			const Foo e{ 50 };
			const Foo f{ 60 };

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);

				// check that copy of list matches list
				Vector<Foo> copyOfList{ list };
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(list.Front(), copyOfList.Front());
				Assert::AreEqual(list.Back(), copyOfList.Back());
				Assert::AreEqual(a, copyOfList.Front());
				Assert::AreEqual(c, copyOfList.Back());
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				list.PushBack(d);
				list.PushBack(e);
				list.PushBack(f);
				Assert::AreEqual(size_t(6), list.Size());
				Assert::AreEqual(a, list.Front());
				Assert::AreEqual(f, list.Back());

				// Copy contents of list into listTwo
				Vector<Foo> listTwo(list);
				Assert::AreEqual(size_t(6), list.Size());
				Assert::AreEqual(a, list.Front());
				Assert::AreEqual(f, list.Back());

				// Check each node in each list to ensure they are the same 
				for (size_t i = 0; i < list.Size(); i++)
				{
					list.PopBack();
					listTwo.PopBack();
					Assert::AreEqual(listTwo.Back(), list.Back());
				}
			}

			{
				Vector<Foo> list;
				Vector<Foo> listTwo;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				listTwo = list;
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), listTwo.Size());
				Assert::AreEqual(listTwo.Front(), list.Front());
				Assert::AreEqual(listTwo.Back(), list.Back());
			}
		}

		TEST_METHOD(Destructor)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };
			{
				Vector<Foo> list = { a,b,c };
				Assert::AreEqual(a, list[0]);
				Assert::AreEqual(b, list[1]);
				Assert::AreEqual(c, list[2]);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				list.~Vector();
				Assert::AreEqual(size_t(0), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
			}
		}

		TEST_METHOD(IteratorDereference)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			//Iterator
			{
				Vector<Foo> list = { a,b,c };
				Vector<Foo>::Iterator it(list.begin());
				Assert::AreEqual(a, *it);
			}

			{
				Vector<Foo> list;
				Vector<Foo>::Iterator it(list.begin());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}

			{
				Vector<Foo>::Iterator it;
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}

			// ConstIterator
			{
				Vector<Foo> list = { a,b,c };
				Vector<Foo>::ConstIterator it(list.begin());
				Assert::AreEqual(a, *it);
			}

			{
				Vector<Foo> list;
				Vector<Foo>::ConstIterator it(list.begin());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}

			{
				Vector<Foo>::ConstIterator it;
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}
		}

		TEST_METHOD(IteratorConstructor)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::ExpectException<std::runtime_error>([&list]() {Vector<Foo>::Iterator it(list,4); });
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
		
				Vector<Foo>::Iterator it(list.begin());
				Vector<Foo>::ConstIterator itTwo(it);
				Vector<Foo>::ConstIterator itThree = list.cbegin();
				Assert::AreEqual(*it, *itTwo);
				Assert::AreEqual(*itThree, *itTwo);
			}

			{
				Vector<Foo> list = { a,b,c };
				Vector<Foo>::Iterator it(list.begin());
				Vector<Foo>::ConstIterator itTwo(it);
				Vector<Foo>::ConstIterator itThree = list.cbegin();
				Assert::AreEqual(*it, *itTwo);
				Assert::AreEqual(*itThree, *itTwo);
			}

			{
				Vector<Foo> list = { a,b,c };
				const Vector<Foo>& listTwo = list;
				Vector<Foo>::ConstIterator it(listTwo.begin());
				Assert::AreEqual(*it, a);
			}
		}

		TEST_METHOD(BeginAndEnd)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
				Vector<Foo> list;
				Vector<Foo>::Iterator it(list.begin());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; UNREFERENCED_LOCAL(it); });
			}

			{
				Vector<Foo> list = { a,b,c };
				Vector<Foo>::Iterator it(list.begin());
				Assert::AreEqual(a, *it);
			}

			{
				const Vector<Foo> list = { a,b,c };
				Vector<Foo>::ConstIterator it(list.cbegin());
				Assert::AreEqual(a, *it);
			}

			{
				const Vector<Foo> list = { a,b,c };
				Vector<Foo>::ConstIterator it(list.begin());
				Assert::AreEqual(a, *it);
			}

			{
				Vector<Foo> list;
				Vector<Foo>::Iterator it(list.end());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; UNREFERENCED_LOCAL(it); });
			}

			{
				Vector<Foo> list = { a,b,c };
				Vector<Foo>::Iterator it(list.end());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}

			{
				Vector<Foo> list;
				const Vector<Foo>& listTwo = list;
				Vector<Foo>::ConstIterator it(listTwo.cend());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}

			{
				const Vector<Foo> list = { a,b,c };
				Vector<Foo>::ConstIterator it(list.end());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}
		}

		TEST_METHOD(IteratorEquality)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			//Iterator
			{
				Vector<Foo> list;
				Vector<Foo> listTwo;
				Vector<Foo>::Iterator it(list.begin());
				Vector<Foo>::Iterator itTwo(it);
				Assert::IsTrue(it == itTwo);

				itTwo = listTwo.begin();
				Assert::IsTrue(it != itTwo);

				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Vector<Foo>::Iterator itThree(list.begin());
				Vector<Foo>::Iterator itFour(list.begin());
				Assert::AreEqual(a, *itThree);
				Assert::AreEqual(a, *itFour);
				Assert::IsTrue(itThree == itFour);
				++itThree;
				Assert::IsFalse(itThree == itFour);
			}

			// ConstIterator
			{
				Vector<Foo> list;
				Vector<Foo> listTwo;
				Vector<Foo>::ConstIterator it(list.begin());
				Vector<Foo>::ConstIterator itTwo(it);
				Assert::IsTrue(it == itTwo);

				itTwo = listTwo.begin();
				Assert::IsTrue(it != itTwo);

				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Vector<Foo>::ConstIterator itThree(list.begin());
				Vector<Foo>::ConstIterator itFour(list.begin());
				Assert::AreEqual(a, *itThree);
				Assert::AreEqual(a, *itFour);
				Assert::IsTrue(itThree == itFour);
				++itThree;
				Assert::IsFalse(itThree == itFour);
			}
		}

		TEST_METHOD(IteratorIncrementor)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			//Iterator
			{
				Vector<Foo> list;
				Vector<Foo>::Iterator it(list.begin());
				Assert::ExpectException<std::runtime_error>([&it]() { Vector<Foo>::Iterator itTwo(it++);; });
			}

			{
				Vector<Foo>::Iterator it;
				Assert::ExpectException<std::runtime_error>([&it]() { it++; });
				Assert::ExpectException<std::runtime_error>([&it]() { ++it; });
				Vector<Foo>::ConstIterator itTwo;
				Assert::ExpectException<std::runtime_error>([&itTwo]() { itTwo++; });
				Assert::ExpectException<std::runtime_error>([&itTwo]() { ++itTwo; });
			}

			{
				Vector<Foo> list = { a,b,c };
				Vector<Foo>::Iterator it(list.begin());
				Assert::AreEqual(a, *it);
				++it;
				Assert::AreEqual(b, *it);
				Vector<Foo>::Iterator itTwo(it++);

				Assert::AreEqual(c, *it);
			}

			// ConstIterator
			{
				Vector<Foo> list;
				Vector<Foo>::ConstIterator it(list.begin());
				Assert::ExpectException<std::runtime_error>([&it]() { Vector<Foo>::ConstIterator itTwo(it++);; });
			}

			{
				Vector<Foo> list = { a,b,c };
				Vector<Foo>::ConstIterator it(list.begin());
				Assert::AreEqual(a, *it);
				++it;
				Assert::AreEqual(b, *it);
				it++;
				Assert::AreEqual(c, *it);
			}
		}

		TEST_METHOD(Reserve)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				list.Reserve(2);
				Assert::AreEqual(size_t(3), list.Capacity());
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				list.Reserve(10);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(10), list.Capacity());
				list.Reserve(4);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(10), list.Capacity());
			}
		}

		TEST_METHOD(SizeAndCapacity)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };
			{
				Vector<Foo> list = { a,b,c };
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				list.PopBack();
				Assert::AreEqual(size_t(2), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
			}
		}

		TEST_METHOD(IsEmpty)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };

			{
				Vector<Foo> list;
				Assert::AreEqual(true,list.IsEmpty());
				Assert::IsTrue( list.IsEmpty());
			}

			{
				Vector<Foo> list = { a,b,c };
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				Assert::AreEqual(false, list.IsEmpty());
				Assert::IsFalse(list.IsEmpty());
			}
		}
		TEST_METHOD(FrontAndBack)
		{
			{
				Foo a{ 10 };
				Foo b{ 20 };
				Foo c{ 30 };

				{
					Vector<Foo> list;
					Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
					Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
				}

				{
					Vector<Foo> list;
					list.PushBack(a);
					Assert::AreEqual(a, list.Front());
					Assert::AreEqual(a, list.Back());
					list.PushBack(b);
					Assert::AreEqual(a, list.Front());
					Assert::AreEqual(b, list.Back());
					list.PushBack(c);
					Assert::AreEqual(a, list.Front());
					Assert::AreEqual(c, list.Back());
				}
			}

			{
				const Foo a{ 10 };
				const Foo b{ 20 };
				const Foo c{ 30 };

				{
					const Vector<Foo> list;
					Assert::AreEqual(size_t(0), list.Size());
					Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
					Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
				}

				{
					const Vector<Foo> list = { a,b };
					Assert::AreEqual(size_t(2), list.Size());
					Assert::AreEqual(a, list.Front());
					Assert::AreEqual(b, list.Back());
				}

				{
					Vector<Foo> list;
					Assert::AreEqual(size_t(0), list.Size());

					// Check for one element in list
					list.PushBack(a);
					Assert::AreEqual(size_t(1), list.Size());
					Assert::AreEqual(a, list.Front());
					Assert::AreEqual(a, list.Back());
					// Check for two elements in List
					list.PushBack(b);
					Assert::AreEqual(size_t(2), list.Size());
					Assert::AreEqual(a, list.Front());
					Assert::AreEqual(b, list.Back());
				}
			}
		}

		TEST_METHOD(PopBack)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };

			{
				Vector<Foo> list = { a,b,c };
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				list.PopBack();
				Assert::AreEqual(size_t(2), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
			}
		}

		TEST_METHOD(Clear)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };

			{
				Vector<Foo> list = { a,b,c };
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				list.Clear();
				Assert::AreEqual(size_t(0), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
			}
		}

		TEST_METHOD(PushBack)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };
			const Foo d{40};
			{
				Vector<Foo> list;
				Assert::AreEqual(size_t(0), list.Size());
				Assert::AreEqual(size_t(0), list.Capacity());
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				list.PushBack(d);
				Assert::AreEqual(size_t(4), list.Size());
				Assert::AreEqual(size_t(4), list.Capacity());

			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);

				Vector<Foo> copyOfList(std::move(list));
				Assert::AreEqual(size_t(3), copyOfList.Size());
				Assert::AreEqual(a, copyOfList.Front());
				Assert::AreEqual(c, copyOfList.Back());
				copyOfList.PushBack(Foo(50));
				Assert::AreEqual(size_t(4), copyOfList.Size());
				Assert::AreEqual(a, copyOfList.Front());
				Assert::AreEqual(Foo(50), copyOfList.Back());
			}
		}

		TEST_METHOD(ShrinkToFit)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };
			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				list.ShrinkToFit();
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				list.Reserve(10);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(10), list.Capacity());
				list.ShrinkToFit();
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
			}
		}

		TEST_METHOD(At)
		{
			Foo a{ 10 };
			Foo b{ 20 };
			Foo c{ 30 };
			const Foo d{ 40 };
			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				Assert::AreEqual(list.At(0), a);
				Assert::AreEqual(list.At(1), b);
				Assert::AreEqual(list.At(2), c);
				Assert::ExpectException<std::runtime_error>([&list]() {auto& data = list.At(3); UNREFERENCED_LOCAL(data ); });
			}

			{
				const Vector<Foo> list = { a,b,c };
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(size_t(3), list.Capacity());
				Assert::AreEqual(list.At(0), a);
				Assert::AreEqual(list.At(1), b);
				Assert::AreEqual(list.At(2), c);
				Assert::ExpectException<std::runtime_error>([&list]() {auto& data = list.At(3); UNREFERENCED_LOCAL(data); });
			}
		}

		TEST_METHOD(Find)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			// Iterator
			{
				// List with elements within but not the value looking for
				Vector<Foo> list = { a,b };
				Vector<Foo>::Iterator it = list.Find(c);
				Assert::AreEqual(it, list.end());

				// Empty List
				Vector<Foo> listTwo;
				Vector<Foo>::Iterator itTwo = listTwo.Find(a);
				Assert::AreEqual(itTwo, listTwo.end());

				// List with elements within with the value looking for
				Vector<Foo>::Iterator itThree = list.Find(a);
				Assert::AreEqual(a, *itThree);
			}

			// ConstIterator
			{
				const Vector<Foo> list = { a,b };
				// List with elements within but not the value looking for
				const Vector<Foo>& listTwo = list;
				Vector<Foo>::ConstIterator it = listTwo.Find(c);
				Assert::AreEqual(it, listTwo.cend());

				// List with elements within with the value looking for
				const Vector<Foo>& listFour{ list };
				Vector<Foo>::ConstIterator itThree = listFour.Find(a);
				Assert::AreEqual(a, *itThree);
			}
		}
		TEST_METHOD(Remove)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };
			const Foo d{ 40 };
			const Foo e{ 50 };
			const Foo f{ 60 };

			{
				Vector<Foo> list;
				Vector<Foo> listTwo;
				Vector<Foo>::Iterator it(list.begin());
				Vector<Foo>::Iterator itTwo(listTwo.begin());

				bool check = false;
				Assert::ExpectException<std::runtime_error>([&check, &list, &itTwo, &a]() { check = list.Remove(itTwo); UNREFERENCED_LOCAL(check); });
			}

			{
				Vector<Foo> list;
				Assert::AreEqual(list.Remove(list.begin()), false);
			}

			{
				Vector<Foo> list;
				Assert::AreEqual(list.Remove(c), false);
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				Assert::AreEqual(list.Size(), size_t(2));
				Assert::AreEqual(list.Remove(list.begin()), true);
				Assert::AreEqual(list.Size(), size_t(1));
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				Assert::AreEqual(list.Size(), size_t(2));
				Assert::AreEqual(list.Remove(list.Find(b)), true);
				Assert::AreEqual(list.Size(), size_t(1));
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				list.PushBack(d);
				list.PushBack(e);
				list.PushBack(f);
				Assert::AreEqual(list.Size(), size_t(6));
				Assert::AreEqual(list.Remove(f), true);
				Assert::AreEqual(list.Size(), size_t(5));
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::AreEqual(list.Size(), size_t(3));
				Assert::AreEqual(list.Remove(b), true);
				Assert::AreEqual(list.Size(), size_t(2));
			}

			{
				Vector<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				list.PushBack(d);
				list.PushBack(e);
				list.PushBack(f);
				Assert::AreEqual(list.Size(), size_t(6));
				Assert::AreEqual(list.Remove(c), true);
				Assert::AreEqual(list.Size(), size_t(5));
			}
		}
	private:
		inline static _CrtMemState _startMemState;
	};
}