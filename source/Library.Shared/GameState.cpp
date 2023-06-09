#include"pch.h"
#include "GameState.h"

namespace FIEAGameEngine
{
	GameState::GameState()
	{
		_eventQueue = new EventQueue();
	}
	GameState::~GameState()
	{
		delete _eventQueue;
	}
	GameTime& GameState::GetGameTime()
	{
		return _gameTime;
	}
	void GameState::SetGameTime(GameTime& gameTime)
	{
		_gameTime = gameTime;
	}
	float GameState::GetDeltaTime() const
	{
		auto time = _gameTime.ElapsedGameTime();
		float deltaTime = static_cast<float>(time.count());
		deltaTime /= 1000;

		return deltaTime;
	}
	EventQueue& GameState::GetEventQueue()
	{
		return *_eventQueue;
	}

	/*void GameState::EnqueueAction(Action* action)
	{
		_actionsQueue.PushBack(action);
	}*/

	void GameState::Clear()
	{
		_eventQueue->Clear();
	}

}
