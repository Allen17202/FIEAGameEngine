#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"
#include "Foo.h"
#include "ToStringSpecializations.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(SListTests)
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
			// Default Constructor for SList
			SList<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
		}

		TEST_METHOD(IteratorConstructor)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
				SList<Foo> list = { a,b,c };
				SList<Foo>::Iterator it(list.begin());
				SList<Foo>::ConstIterator itTwo(it);
				SList<Foo>::ConstIterator itThree = list.cbegin();
				Assert::AreEqual(*it, *itTwo);
				Assert::AreEqual(*itThree, *itTwo);
			}

			{
				SList<Foo> list = { a,b,c };
				const SList<Foo>& listTwo = list;
				SList<Foo>::ConstIterator it(listTwo.begin());
				Assert::AreEqual(*it, a);
			}

			{
				const SList<Foo>& list = { a,b,c };
				SList<Foo>::Iterator it(list);
				SList<Foo>::ConstIterator itTwo(list);
				SList<Foo>::ConstIterator itThree = list.cbegin();
				Assert::AreEqual(*it, *itTwo);
				Assert::AreEqual(*itThree, *itTwo);
			}
		}

		TEST_METHOD(IteratorIncrementor)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			//Iterator
			{
				SList<Foo> list;
				SList<Foo>::Iterator it(list.begin());

				SList<Foo>::Iterator itTwo(it++);
				Assert::ExpectException<std::runtime_error>([&itTwo]() { *itTwo; UNREFERENCED_LOCAL(itTwo); });
			}

			{
				SList<Foo>::Iterator it;
				Assert::ExpectException<std::runtime_error>([&it]() { it++; });
				Assert::ExpectException<std::runtime_error>([&it]() { ++it; });
				SList<Foo>::ConstIterator itTwo;
				Assert::ExpectException<std::runtime_error>([&itTwo]() { itTwo++; });
				Assert::ExpectException<std::runtime_error>([&itTwo]() { ++itTwo; });
			}

			{
				SList<Foo> list = { a,b,c };
				SList<Foo>::Iterator it(list.begin());
				Assert::AreEqual(a, *it);
				++it;
				Assert::AreEqual(b, *it);
				SList<Foo>::Iterator itTwo(it++);

				Assert::AreEqual(c, *it);
			}

			// ConstIterator
			{
				SList<Foo> list = { a,b,c };
				SList<Foo>::ConstIterator it(list.begin());
				Assert::AreEqual(a, *it);
				++it;
				Assert::AreEqual(b, *it);
				it++;
				Assert::AreEqual(c, *it);
			}
		}

		TEST_METHOD(IteratorDereference)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			//Iterator
			{
				SList<Foo> list = { a,b,c };
				SList<Foo>::Iterator it(list.begin());
				Assert::AreEqual(a, *it);
			}

			// ConstIterator
			{
				SList<Foo> list = { a,b,c };
				SList<Foo>::ConstIterator it(list.begin());
				Assert::AreEqual(a, *it);
			}

			{
				SList<Foo> list;
				SList<Foo>::ConstIterator it(list.begin());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });


				//Assert::AreEqual(a, *it);
			}
		}

		TEST_METHOD(InsertAfter)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
				SList<Foo> list;
				SList<Foo> listTwo;
				SList<Foo>::Iterator it(list.begin());
				SList<Foo>::Iterator itTwo(listTwo.begin());
				SList<Foo>::Iterator itThree;
				Assert::ExpectException<std::runtime_error>([&itThree,&list,&itTwo,&a]() { itThree = list.InsertAfter(itTwo, a); });
			}

			{
				// InsertAfter into a empty List
				SList<Foo> list;
				SList<Foo>::Iterator it(list.begin());
				SList<Foo>::Iterator itTwo = list.InsertAfter(it, a);
				Assert::AreEqual(list.Front(), a);
				Assert::AreEqual(list.Back(), a);
				Assert::AreEqual(*itTwo, a);

				// Insert with a single node in linked list
				SList<Foo>::Iterator itThree = list.InsertAfter(list.end(), b);
				Assert::AreEqual(list.Front(), a);
				Assert::AreEqual(list.Back(), b);
				Assert::AreEqual(*itThree, b);

				// Insert between multiple nodes in linked list
				SList<Foo>::Iterator itFour = list.InsertAfter(list.begin(), c);
				Assert::AreEqual(list.Front(), a);
				Assert::AreEqual(list.Back(), b);
				Assert::AreEqual(*itFour, c);

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
				SList<Foo> list = { a,b };
				SList<Foo>::Iterator it = list.Find(c);
				Assert::AreEqual(it, list.end());

				// Empty List
				SList<Foo> listTwo;
				SList<Foo>::Iterator itTwo = listTwo.Find(a);
				Assert::AreEqual(itTwo, listTwo.end());

				// List with elements within with the value looking for
				SList<Foo>::Iterator itThree = list.Find(a);
				Assert::AreEqual(a, *itThree);
			}

			// ConstIterator
			{
				const SList<Foo> list = { a,b };
				// List with elements within but not the value looking for
				const SList<Foo>& listTwo = list;
				SList<Foo>::ConstIterator it = listTwo.Find(c);
				Assert::AreEqual(it, listTwo.cend());

				// List with elements within with the value looking for
				const SList<Foo>& listFour{ list };
				SList<Foo>::ConstIterator itThree = listFour.Find(a);
				Assert::AreEqual(a, *itThree);
			}
		}

		TEST_METHOD(IteratorEquality)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			//Iterator
			{
				SList<Foo> list;
				SList<Foo> listTwo;
				SList<Foo>::Iterator it(list.begin());
				SList<Foo>::Iterator itTwo(it);
				Assert::IsTrue(it == itTwo);

				itTwo = listTwo.begin();
				Assert::IsTrue(it != itTwo);

				list.PushFront(a);
				list.PushFront(b);
				list.PushFront(c);
				SList<Foo>::Iterator itThree(list.begin());
				SList<Foo>::Iterator itFour(list.begin());
				Assert::AreEqual(c, *itThree);
				Assert::AreEqual(c, *itFour);
				Assert::IsTrue(itThree == itFour);
				++itThree;
				Assert::IsFalse(itThree == itFour);
			}

			// ConstIterator
			{
				SList<Foo> list;
				SList<Foo> listTwo;
				SList<Foo>::ConstIterator it(list.begin());
				SList<Foo>::ConstIterator itTwo(it);
				Assert::IsTrue(it == itTwo);

				itTwo = listTwo.begin();
				Assert::IsTrue(it != itTwo);

				list.PushFront(a);
				list.PushFront(b);
				list.PushFront(c);
				SList<Foo>::ConstIterator itThree(list.begin());
				SList<Foo>::ConstIterator itFour(list.begin());
				Assert::AreEqual(c, *itThree);
				Assert::AreEqual(c, *itFour);
				Assert::IsTrue(itThree == itFour);
				++itThree;
				Assert::IsFalse(itThree == itFour);
			}
		}

		TEST_METHOD(Begin)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
				SList<Foo> list;
				SList<Foo>::Iterator it(list.begin());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; UNREFERENCED_LOCAL(it); });
			}

			{
				SList<Foo> list = { a,b,c };
				SList<Foo>::Iterator it(list.begin());
				Assert::AreEqual(a, *it);
			}

			{
				const SList<Foo> list = { a,b,c };
				SList<Foo>::ConstIterator it(list.cbegin());
				Assert::AreEqual(a, *it);
			}

			{
				const SList<Foo> list = { a,b,c };
				SList<Foo>::ConstIterator it(list.begin());
				Assert::AreEqual(a, *it);
			}
		}

		TEST_METHOD(End)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
				SList<Foo> list;
				SList<Foo>::Iterator it(list.end());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; UNREFERENCED_LOCAL(it); });
			}

			{
				SList<Foo> list = { a,b,c };
				SList<Foo>::Iterator it(list.end());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			
			}

			{
				SList<Foo> list;
				const SList<Foo>& listTwo = list;
				SList<Foo>::ConstIterator it(listTwo.end());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}

			{
				const SList<Foo> list = { a,b,c };
				SList<Foo>::ConstIterator it(list.end());
				Assert::ExpectException<std::runtime_error>([&it]() { *it; });
			}
		}

		TEST_METHOD(InitializerListConstructor)
		{
			// Default Constructor for SList

			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			SList<Foo> list = { a,b,c };
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(c, list.Back());
		}

		TEST_METHOD(Front)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
				const SList<Foo> list;
				Assert::AreEqual(size_t(0), list.Size());
				Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			}

			{
				const SList<Foo> list = {a,b};
				Assert::AreEqual(size_t(2), list.Size());
				Assert::AreEqual(a, list.Front());
				Assert::AreEqual(b, list.Back());
			}

			{
				SList<Foo> list;
				Assert::AreEqual(size_t(0), list.Size());

				// Check for one element in list
				list.PushFront(a);
				Assert::AreEqual(size_t(1), list.Size());
				Assert::AreEqual(a, list.Front());

				// Check for two elements in List
				list.PushBack(b);
				Assert::AreEqual(size_t(2), list.Size());
				Assert::AreEqual(a, list.Front());
				Assert::AreEqual(b, list.Back());
			}


		}

		TEST_METHOD(Back)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
		
				const SList<Foo> list;
				Assert::AreEqual(size_t(0), list.Size());
				Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Back(); UNREFERENCED_LOCAL(front); });
			
			}


			{
				SList<Foo> list;
				Assert::AreEqual(size_t(0), list.Size());

				// Check for one element in list
				list.PushFront(a);
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

		TEST_METHOD(Clear)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			// Check for empty List
			SList<Foo> list;
			Assert::IsTrue(list.IsEmpty());

			list.PushFront(a);
			list.PushFront(b);
			list.PushFront(c);

			// Check that the list is not empty and that size is correct, and front and back are correct nodes 
			Assert::IsFalse(list.IsEmpty());
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(c, list.Front());
			Assert::AreEqual(a, list.Back());

			list.Clear();

			// Check list is empty and that front and back is nullptr
			Assert::IsTrue(list.IsEmpty());
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
		}

		TEST_METHOD(Size)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			// Check for empty list
			SList<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());

			// Check for one element in list
			list.PushFront(a);
			Assert::AreEqual(size_t(1), list.Size());

			// Check for two element in list
			list.PushFront(b);
			Assert::AreEqual(size_t(2), list.Size());

			// Check for three element in list
			list.PushFront(c);
			Assert::AreEqual(size_t(3), list.Size());

			// Check for one element in list
			list.Clear();
			Assert::AreEqual(size_t(0), list.Size());
		}

		TEST_METHOD(PushFront)
		{

			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };
			SList<Foo> list;

			// Check that push front works for one element
			list.PushFront(a);
			Assert::AreEqual(size_t(1), list.Size());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(a, list.Back());

			// Check that push front works for two element
			list.PushFront(b);
			Assert::AreEqual(size_t(2), list.Size());
			Assert::AreEqual(b, list.Front());
			Assert::AreEqual(a, list.Back());

			// Check that push front works for three element
			list.PushFront(c);
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(c, list.Front());
			Assert::AreEqual(a, list.Back());
			list.Clear();
		}

		TEST_METHOD(PopFront)
		{

			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() {list.PopFront(); });

			list.PushFront(a);
			list.PushFront(b);
			list.PushFront(c);
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(c, list.Front());
			Assert::AreEqual(a, list.Back());

			// Check Pop front for one element
			list.PopFront();
			Assert::AreEqual(size_t(2), list.Size());
			Assert::AreEqual(b, list.Front());
			Assert::AreEqual(a, list.Back());

			// Check pop front for two elements
			list.PopFront();
			Assert::AreEqual(size_t(1), list.Size());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(a, list.Back());

			// Check pop front for three elements
			list.PopFront();
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });

			list.Clear();
		}

		TEST_METHOD(PushBack)
		{

			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };
			SList<Foo> list;
			SList<Foo>::Iterator it = list.PushBack(a);
			// Pushing node to back of list, one element
			Assert::AreEqual(size_t(1), list.Size());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(a, list.Back());
			Assert::AreEqual(a, *it);

			// Pushing node to back of list, two element
			list.PushBack(b);
			Assert::AreEqual(size_t(2), list.Size());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(b, list.Back());

			// Pushing node to back of list, three element
			list.PushBack(c);
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(c, list.Back());
			list.Clear();
		}

		TEST_METHOD(PopBack)
		{
			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			{
				SList<Foo> list{a};
				Assert::AreEqual(size_t(1), list.Size());
				list.PopBack();
				Assert::AreEqual(size_t(0), list.Size());
			}

			{
				SList<Foo> list;
				Assert::ExpectException<std::runtime_error>([&list]() {list.PopBack(); });
				list.PushBack(a);
				Assert::AreEqual(size_t(1), list.Size());
				list.PopBack();
				Assert::AreEqual(size_t(0), list.Size());
			}

			{
				SList<Foo> list;

				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(a, list.Front());
				Assert::AreEqual(c, list.Back());

				// Check size and that popped back node updates accordingly
				list.PopBack();
				Assert::AreEqual(size_t(2), list.Size());
				Assert::AreEqual(a, list.Front());
				Assert::AreEqual(b, list.Back());

				// Check size and that popped back node updates accordingly
				list.PopBack();
				Assert::AreEqual(size_t(1), list.Size());
				Assert::AreEqual(a, list.Front());
				Assert::AreEqual(a, list.Back());

				// Check size and that popped back node updates accordingly
				list.PopBack();
				Assert::AreEqual(size_t(0), list.Size());
				Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
				Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });

				list.Clear();
			}
		}

		TEST_METHOD(isEmpty)
		{
			// Check for empty list
			SList<Foo> list;
			Assert::AreEqual(true, list.IsEmpty());


			const Foo a{ 10 };
			const Foo b{ 20 };
			const Foo c{ 30 };

			// Check for full list
			list.PushFront(a);
			list.PushFront(b);
			list.PushFront(c);
			Assert::AreEqual(false, list.IsEmpty());
			list.Clear();

			// Check for empty list after clearing
			Assert::AreEqual(true, list.IsEmpty());
			list.Clear();
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
				SList<Foo> list;
				SList<Foo> listTwo;
				SList<Foo>::Iterator it(list.begin());
				SList<Foo>::Iterator itTwo(listTwo.begin());

				bool check = false;
				Assert::ExpectException<std::runtime_error>([&check, &list, &itTwo, &a]() { check = list.Remove(itTwo); UNREFERENCED_LOCAL(check); });
			}

			{
				SList<Foo> list;
				list.Remove(list.begin());
			    Assert::AreEqual(list.Remove(list.begin()), false);
			}
			
			{
				SList<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				Assert::AreEqual(list.Size(), size_t(2));
				list.Remove(list.begin());
				Assert::AreEqual(list.Size(), size_t(1));
			}

			{
				SList<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				Assert::AreEqual(list.Size(), size_t(2));
				list.Remove(c);
				Assert::AreEqual(list.Size(), size_t(2));
				Assert::IsFalse(list.Remove(c));
			}

			{
				SList<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				list.PushBack(d);
				list.PushBack(e);
				list.PushBack(f);
				Assert::AreEqual(list.Size(), size_t(6));
				list.Remove(f);
				Assert::AreEqual(list.Size(), size_t(5));

			}

			{
				SList<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				Assert::AreEqual(list.Size(), size_t(3));
				list.Remove(b);
				Assert::AreEqual(list.Size(), size_t(2));
			}

			{
				SList<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);
				list.PushBack(d);
				list.PushBack(e);
				list.PushBack(f);
				Assert::AreEqual(list.Size(), size_t(6));
				list.Remove(c);
				Assert::AreEqual(list.Size(), size_t(5));
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
				SList<Foo> list;
				list.PushBack(a);
				list.PushBack(b);
				list.PushBack(c);

				// check that copy of list matches list
				SList<Foo> copyOfList{ list };
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(list.Front(), copyOfList.Front());
				Assert::AreEqual(list.Back(), copyOfList.Back());
				Assert::AreEqual(a, copyOfList.Front());
				Assert::AreEqual(c, copyOfList.Back());
			}

			{
				SList<Foo> list;
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
				SList<Foo> listTwo(list);
				Assert::AreEqual(size_t(6), list.Size());
				Assert::AreEqual(a, list.Front());
				Assert::AreEqual(f, list.Back());

				// Check each node in each list to ensure they are the same 
				for (size_t i = 0; i < list.Size(); i++)
				{
					list.PopFront();
					listTwo.PopFront();
					Assert::AreEqual(listTwo.Front(), list.Front());
				}
			}

			{
				SList<Foo> list;
				SList<Foo> listTwo;
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
		private:
			inline static _CrtMemState _startMemState;
	};
}
