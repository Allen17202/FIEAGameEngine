#include "pch.h"
#include "CppUnitTest.h"
#include "Allocator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(AllocatorTests)
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

		TEST_METHOD(BumpAllocator)
		{
			constexpr std::size_t memSize = 1024;
			std::byte mem[memSize];
		
			FIEAGameEngine::BumpAllocator<int> bumpAllocator(memSize, mem);
			FIEAGameEngine::BumpAllocator<int> bumpAllocatorZero(0, mem);
			int* testOne = bumpAllocator.allocate();
			Assert::IsTrue(testOne != nullptr);
			bumpAllocator.deallocate(testOne, 1, 1);
			Assert::IsTrue(testOne != nullptr);
			int* testTwo = bumpAllocatorZero.allocate(0);
			Assert::IsTrue(testTwo == nullptr);
			Assert::ExpectException<std::bad_alloc>([&bumpAllocator]() {int* front = bumpAllocator.allocate(2054); UNREFERENCED_LOCAL(front);});
		
			int* testThree = static_cast<int*>(bumpAllocator.do_allocate(sizeof(int), alignof(int)));
			Assert::IsTrue(testThree != nullptr);
			Assert::IsTrue(testOne == testOne);
			Assert::IsTrue(testOne != testTwo);
			Assert::IsFalse(bumpAllocator.do_is_equal(bumpAllocatorZero));


			std::pmr::polymorphic_allocator<int> polyInt(&bumpAllocator);
			int* testFive = polyInt.allocate(64);
			Assert::IsNotNull(testFive);
			polyInt.deallocate(testFive, 64);
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}