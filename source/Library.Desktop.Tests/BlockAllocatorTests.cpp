#include "pch.h"
#include "CppUnitTest.h"
#include "BlockAllocator.h"

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

		TEST_METHOD(BlockAllocator)
		{
			{
				FIEAGameEngine::BlockAllocator<int> blockAllocator(sizeof(int), 10);
				std::pmr::polymorphic_allocator<int> polyInt(&blockAllocator);

				int* testOne = polyInt.allocate(1);
				Assert::IsNotNull(testOne);
				Assert::IsTrue(reinterpret_cast<std::uintptr_t>(testOne) % alignof(int) == 0);
				polyInt.deallocate(testOne, 1);
			}
			
			{
				FIEAGameEngine::BlockAllocator<int> blockAllocator(sizeof(int), 10);
				std::pmr::polymorphic_allocator<int> polyInt(&blockAllocator);

				int* testOne = polyInt.allocate(1);
				Assert::IsNotNull(testOne);

				int* testTwo = polyInt.allocate(1);
				Assert::IsNotNull(testTwo);

				polyInt.deallocate(testOne, 1);
				polyInt.deallocate(testTwo, 1);
			}

			{
				FIEAGameEngine::BlockAllocator<int> blockAllocator(sizeof(int), 25);
				FIEAGameEngine::BlockAllocator<int> blockAllocatorZero(sizeof(int), 0);
				Assert::ExpectException<std::runtime_error>([]() { FIEAGameEngine::BlockAllocator<int> blockAllocator(3, 17);; });

				Assert::IsFalse(blockAllocator.do_is_equal(blockAllocatorZero));
				Assert::ExpectException<std::out_of_range>([&blockAllocator]() { int* testThree = static_cast<int*>(blockAllocator.do_allocate(256, alignof(std::max_align_t) + 1));UNREFERENCED_LOCAL(testThree); });
			}

			{
				FIEAGameEngine::BlockAllocator<int> blockAllocator(sizeof(int), 10);
				std::pmr::polymorphic_allocator<int> polyInt(&blockAllocator);

				int* testOne = polyInt.allocate(2);
				testOne[0] = 25;
				testOne[1] = 47;
				Assert::IsNotNull(testOne);
				Assert::ExpectException<std::out_of_range>([&blockAllocator]() { int* testThree = static_cast<int*>(blockAllocator.do_allocate(50, alignof(int))); UNREFERENCED_LOCAL(testThree); });
				polyInt.deallocate(testOne, 2);
			}

		}

	private:
		inline static _CrtMemState _startMemState;
	};
}