#pragma once
enum class SceneTable
{
	MainScene,
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void StartGame(); //���� ����
	void EndGame(); //���� ����	
	void LoadScene(SceneTable Scene); //�� �ҷ�����
	
private:
	SceneTable SelectScene;

	bool isGameEnd;
	void* currentScene;

	template<typename T> void StartScene();
	void EndScene();
};

static SceneManager sceneManager; //��Ŭ��



