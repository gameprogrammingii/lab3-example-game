#pragma once

#include "Screen.h"
#include "AssetManager.h"

#include <vector>

using namespace std;

class GameObject;
class Game;

class State
{
protected:
	Game* game;
public:
	State(Game* game) { this->game = game; }
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
};

class Game
{
	Screen screen;
	AssetManager assetManager;
	vector<GameObject*> gameObjects;

	void Init();

	State* state;

public:
	void Run();
	Game();
	~Game();
	Screen* GetScreen() { return &screen; }
	AssetManager* GetAssetManager() { return &assetManager; }
	void ClearGameObjects();
	void RenderGameObjects();

	template<typename T>
	T* CreateGameObject()
	{
		T* gameObject = new T();
		gameObject->game = this;
		gameObjects.push_back(gameObject);
		return gameObject;
	}

	template<typename T>
	void SwitchToState()
	{
		if (state != NULL)
		{
			delete state;
			state = NULL;
		}

		state = new T(this);
		state->Init();
	}
};

