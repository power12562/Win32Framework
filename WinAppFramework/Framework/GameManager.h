#pragma once
enum class SceneTable
{
	MainScene,
};

class GameManager
{
public:
	static GameManager* Gm;

	GameManager();
	~GameManager();

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

