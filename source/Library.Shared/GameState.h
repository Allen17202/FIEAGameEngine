#pragma once
#include "Vector.h"
#include "GameTime.h"
#include "Action.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "Stack.h"

namespace FIEAGameEngine
{
	class GameObject;

	class Game
	{

	};

	class GameState final
	{
	public:
		GameState();
		~GameState();

		GameTime& GetGameTime();
		void SetGameTime(GameTime& gameTime);
		float GetDeltaTime() const;
		EventQueue& GetEventQueue();

		//void Update(GameTime time);
		//void EnqueueAction(Action* action);
		void Clear();
		Stack<Scope*> _scopeStack;
	private:
		//GameObject* _sceneRoot;
		GameTime _gameTime;
		EventQueue* _eventQueue;
		//Vector<Action*> _actionsQueue;
	};
}
