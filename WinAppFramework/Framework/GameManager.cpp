#include "GameManager.h"
#include "..\Scenes\AllScenes.h"

GameManager* GameManager::Gm; //�ܺ� ���ٿ�

GameManager::GameManager()
{
	SelectScene = SceneTable::MainScene;

	currentScene = nullptr;

	isGameEnd = false;
}

GameManager::~GameManager()
{
	
}

//public:
void GameManager::StartGame()
{
	//�� ���� ����
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

void GameManager::EndGame()
{
	EndScene();
	isGameEnd = true;	
}

void GameManager::LoadScene(SceneTable Scene)
{
	EndScene();
	SelectScene = Scene;
}

//private:
template<typename T> void GameManager::StartScene()
{
	T* LoadScene = new T;

	currentScene = LoadScene;

	LoadScene->GameRun();

	delete LoadScene;
}

void GameManager::EndScene()
{
	switch (SelectScene)
	{
	case SceneTable::MainScene:
		((MainScene*)currentScene)->Finalize();
		break;
	}
}


