#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "Event.h"
#include "EventQueue.h"
#include "GameTime.h"
#include "SubscriberFoo.h"
#include "SubscriberRemove.h"
#include "ActionListWhile.h"
#include "ToStringSpecializations.h"
#include "GameObject.h"

#include <chrono>
#include <crtdbg.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;
using namespace FIEAGameEngine;


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EventTests)
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

		TEST_METHOD(EventSubscribeAndRTTI)
		{
			{
				SubscriberFoo subscriber(5);
				Event<Foo>::Subscribe(subscriber);
				Event<Foo>::PendingSubscribersManager();

				Foo f;
				auto eventFoo = std::make_shared<Event<Foo>>(std::move(f));
				eventFoo->Deliver();
				Assert::IsTrue(subscriber._notified);
				subscriber._notified = false;
				Event<Foo>::Unsubscribe(subscriber);
				Event<Foo>::PendingSubscribersManager();
				eventFoo->Deliver();
				Assert::IsFalse(subscriber._notified);
				Event<Foo>::UnSubscribeAll();
			}

			{
				SubscriberRemove subscriber(5);
				SubscriberFoo subscriberTwo(9);
				Event<Foo>::Subscribe(subscriber);
				Event<Foo>::Subscribe(subscriberTwo);
				Event<Foo>::PendingSubscribersManager();

				Foo f;
				auto eventFoo = std::make_shared<Event<Foo>>(std::move(f));
				eventFoo->Deliver();
				Assert::IsTrue(subscriber._notified);
				Assert::IsTrue(subscriberTwo._notified);
				Event<Foo>::PendingSubscribersManager();
				subscriber._notified = false;
				subscriberTwo._notified = false;
				eventFoo->Deliver();
				Assert::IsFalse(subscriber._notified);
				Assert::IsTrue(subscriberTwo._notified);

				Event<Foo>::Unsubscribe(subscriberTwo);
				Event<Foo>::PendingSubscribersManager();
				Event<Foo>::UnSubscribeAll();
			}

			{
				Event<Foo> event;
				EventPublisher* publisher = &event;
				Event<Foo>* eventPointer = publisher->As<Event<Foo>>();
				const Event<Foo>* eventPointerConst = publisher->As<Event<Foo>>();
				EventPublisher* copy = &event;
				Foo f;
				Foo* fPointer = &f;
				Assert::AreEqual(publisher->ToString(), "Event"s);
				Assert::IsTrue(publisher->Is(Event<Foo>::TypeIdClass()));
				Assert::IsTrue(publisher->Is(Event<Foo>::TypeName()));
				Assert::IsTrue(copy->Equals(publisher));
				Assert::IsFalse(copy->Equals(fPointer));
				Assert::IsNotNull(eventPointer);
				Assert::IsNotNull(eventPointerConst);
			}
		}

		TEST_METHOD(EventQueue)
		{
			{
				FIEAGameEngine::EventQueue queue;
				Foo f;
				SubscriberFoo subscriber(5);
				GameTime  g;

				Assert::AreEqual(std::size_t(0), queue.Size());
				Assert::IsTrue(queue.isEmpty());
				auto fooEvent = std::make_shared<Event<Foo>>();
				Assert::AreEqual(fooEvent->Message(), f);
				queue.Enqueue(fooEvent, g);
				Assert::AreEqual(std::size_t(1), queue.Size());

				Event<Foo>::Subscribe(subscriber);
				Event<Foo>::PendingSubscribersManager();
				g.SetCurrentTime(std::chrono::high_resolution_clock::time_point(1s));
				Assert::IsFalse(subscriber._notified);
				queue.Update(g);
				Assert::IsTrue(subscriber._notified);
				Assert::AreEqual(std::size_t(0), queue.Size());

				subscriber._notified = false;
				Assert::IsFalse(subscriber._notified);
				queue.Update(g);
				Assert::IsFalse(subscriber._notified);
				Assert::AreEqual(std::size_t(0), queue.Size());

				Event<Foo>::UnSubscribeAll();
			}

			{
				FIEAGameEngine::EventQueue queue;
				Foo f;
				SubscriberFoo subscriber(5);
				GameTime  g;

				Assert::AreEqual(std::size_t(0), queue.Size());
				Assert::IsTrue(queue.isEmpty());
				auto fooEvent = std::make_shared<Event<Foo>>();
				Assert::AreEqual(fooEvent->Message(), f);
				queue.Enqueue(fooEvent, g);
				Assert::AreEqual(std::size_t(1), queue.Size());
				queue.Clear();
				Assert::AreEqual(std::size_t(0), queue.Size());
				Event<Foo>::UnSubscribeAll();
			}
		}
	private:
		inline static _CrtMemState _startMemState;
	};
}