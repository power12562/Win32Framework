#include "MainScene.h"
#include "..\Framework\WinApp.h"

MainScene::MainScene()
{
	CLIENT_WIDTH = WinApp::GetWinApp().GetClientWidth();
	CLIENT_HEIGHT = WinApp::GetWinApp().GetClientHeight();
}

//씬 시작시 1회 실행
void MainScene::Start()
{
	obj_rect.SetColor(RGB(100, 100, 100)); //색 설정
	obj_rect.SetSquareSize(1000,1000); //크기 설정
	obj_rect.transform.position = Vector2{ CLIENT_WIDTH / 2.f , CLIENT_HEIGHT / 2.f }; //위치 설정

	obj_Sprite.Loadbmp("Resource\\test.bmp"); //리소스 로드
	obj_Sprite.SetTrColor(RGB(255,255,255)); //배경색 제거
}

//1초에 time.FixedUpdatePerSec 만큼 호출 기본값 : 50
void MainScene::FixedUpdate()
{
	

}

//매 프레임 호출
void MainScene::Update()
{	
	//마우스 입력
	input.UpdateMouse();
	Input::MouseState state = input.GetMouseState();

	obj_Sprite.transform.position = Vector2{ state.x, state.y}; //위치 설정

	obj_Sprite.SetAngle(obj_Sprite.GetAngle() + 30 * time.GetDeltatime()); //반시계로 1초에 30도씩 회전

	obj_Sprite.transform.scale += 0.1f * time.GetDeltatime(); //1초에 10% 크기증가

#ifdef _DEBUG
	//printf("mw_X : %d     mw_Y : %d\n", state.x, state.y); //마우스 좌표 확인용
	Vector2 dir = obj_Sprite.GetDir();
	printf("{ %.02f , %.02f  }\n", dir.X, dir.Y);
#endif // _DEBUG
}

//랜더링
void MainScene::Rendering()
{
	obj_rect.Rendering();

	obj_Sprite.Rendering();
}
