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

	void StartGame(); //게임 시작
	void EndGame(); //게임 종료	
	void LoadScene(SceneTable Scene); //씬 불러오기
	
private:
	SceneTable SelectScene;

	bool isGameEnd;
	void* currentScene;

	template<typename T> void StartScene();
	void EndScene();
};

static SceneManager sceneManager; //싱클톤



