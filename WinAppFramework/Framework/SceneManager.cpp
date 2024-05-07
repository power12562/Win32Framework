#include "Scenemanager.h"
#include "..\Scenes\AllScenes.h"

SceneManager::SceneManager()
{
	SelectScene = SceneTable::MainScene;

	currentScene = nullptr;

	isGameEnd = false;
}

SceneManager::~SceneManager()
{
	
}

//public:
void SceneManager::StartGame()
{
	//æ¿ º±≈√ ∑Á«¡
	while (!isGameEnd)
	{
		switch (SelectScene)
		{
		case SceneTable::MainScene:
			StartScene<MainScene>();
			break;
		}
	}
}

void SceneManager::EndGame()
{
	EndScene();
	isGameEnd = true;	
}

void SceneManager::LoadScene(SceneTable Scene)
{
	EndScene();
	SelectScene = Scene;
}

//private:
template<typename T> void SceneManager::StartScene()
{
	T* LoadScene = new T;

	currentScene = LoadScene;

	LoadScene->GameRun();

	delete LoadScene;
}

void SceneManager::EndScene()
{
	switch (SelectScene)
	{
	case SceneTable::MainScene:
		((MainScene*)currentScene)->Finalize();
		break;
	}
}


