#pragma once

#include "Screen.h"
#include "AssetManager.h"

#include <vector>

using namespace std;

class GameObject;
class Game;
class Ball;

class Game
{
	Screen screen;
	AssetManager assetManager;
	vector<GameObject*> gameObjects;

	void Init();

	/*game play*/
	vector<Ball*> balls;
	/*---------*/
public:
	void Run();
	Game();
	~Game();
	Screen* GetScreen() { return &screen; }
	AssetManager* GetAssetManager() { return &assetManager; }
	void ClearGameObjects();
	void RenderGameObjects(Screen* screen);

	template<typename T>
	T* CreateGameObject()
	{
		T* gameObject = new T();
		gameObject->game = this;
		gameObjects.push_back(gameObject);
		return gameObject;
	}

	void DestroyGameObject(GameObject* gameObject);
};

