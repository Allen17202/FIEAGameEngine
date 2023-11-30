#include "pch.h"
#include "CppUnitTest.h"
#include "FreeListAllocator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(FreeListAllocatorTests)
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

		TEST_METHOD(FreeListAllocator)
		{
			{
				FIEAGameEngine::FreeListAllocator<int> freeIntAllocator;
				std::pmr::polymorphic_allocator<int> polyInt(&freeIntAllocator);

				int* testOne = polyInt.allocate(1);
				int* testTwo = polyInt.allocate(1);


				Assert::IsNotNull(testOne);
				Assert::IsNotNull(testTwo);
				polyInt.deallocate(testOne, 64);
				polyInt.deallocate(testTwo, 56);


				int* testThree = static_cast<int*>(freeIntAllocator.do_allocate(64, alignof(int)));
				Assert::IsNotNull(testThree);
				freeIntAllocator.do_deallocate(testThree,64, alignof(int));
				freeIntAllocator.do_deallocate(testOne, 64, alignof(int));
			}

			{
				FIEAGameEngine::FreeListAllocator<int> freeIntAllocator;
			
				int* testOne = static_cast<int*>(freeIntAllocator.do_allocate(1, alignof(int)));
				int* testTwo = static_cast<int*>(freeIntAllocator.do_allocate(2, alignof(int)));
				int* testFour = static_cast<int*>(freeIntAllocator.do_allocate(16, alignof(int)));
				int* testFive = static_cast<int*>(freeIntAllocator.do_allocate(256, alignof(int)));

				Assert::IsNotNull(testOne);
				Assert::IsNotNull(testTwo);
				Assert::IsNotNull(testFour);
				Assert::IsNotNull(testFive);


				freeIntAllocator.do_deallocate(testOne, 1, alignof(int));
				freeIntAllocator.do_deallocate(testTwo, 2, alignof(int));
				freeIntAllocator.do_deallocate(testFour, 16, alignof(int));
				freeIntAllocator.do_deallocate(testFive, 256, alignof(int));
			}

		}


	private:
		inline static _CrtMemState _startMemState;
	};
}