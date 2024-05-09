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
	mario.Loadbmp("Resource\\mario\\mario.bmp"); //리소스 로드
	//obj_Ken.SetAlpha(0.5f); //투명도
	mario.SetTrColor(RGB(153,217,234)); //배경색 제거
	mario.transform.scale = { 5.f, 5.f };

	//애니메이션
	mario_Idle = mario.animation.AddClip(L"Resource\\mario\\Idle.txt");
	mario_Idle->data.frameIntervalTime = 0.02f; //프레임 재생 시간 간격

	mario_Walk = mario.animation.AddClip(L"Resource\\mario\\Walk.txt");
	mario_Walk->data.frameIntervalTime = 0.02f;

	mario.animation.SetClip(mario_Idle); //기본 재생할 클립 설정
	mario.transform.position = Vector2{ CLIENT_WIDTH / 2.f, CLIENT_HEIGHT / 2.f };

	//이미지 반전 여부
	mario.Flip_X = false;
	mario.Flip_Y = false;
}

//1초에 time.FixedUpdatePerSec 만큼 호출 기본값 : 50
void MainScene::FixedUpdate()
{
	

}

//매 프레임 호출
void MainScene::Update()
{	
	//애니메이션 업데이트
	mario.animation.UpdateFrmae(time.GetDeltatime()); 

	//키보드 입력
	bool isLeftRight = true;
	bool isUpDown = true;
	bool isAniEnd = mario.animation.IsClipEnd();
	BoundingBox KenBounds = mario.GetBounds();
	if (input.IsKey(KeyCode::RightArrow) && isAniEnd)
	{
		mario.animation.SetClip(mario_Walk);
		mario.Flip_X = false;

		if (KenBounds.RightBottom.X <= (float)CLIENT_WIDTH)
			mario.transform.position += Vector2::Right * KenMoveSpeed * time.GetDeltatime();
	}
	else if (input.IsKey(KeyCode::LeftArrow) && isAniEnd)
	{
		mario.animation.SetClip(mario_Walk);	
		mario.Flip_X = true;

		if (KenBounds.LefTop.X >= 0)
			mario.transform.position += Vector2::Left * KenMoveSpeed * time.GetDeltatime();
	}
	else
	{
		isLeftRight = false;
	}

	if (input.IsKey(KeyCode::UpArrow) && isAniEnd)
	{
		mario.animation.SetClip(mario_Walk);

		if (KenBounds.LefTop.Y <= (float)CLIENT_HEIGHT)
			mario.transform.position += Vector2::Up * KenMoveSpeed * time.GetDeltatime();
	}
	else if (input.IsKey(KeyCode::DownArrow) && isAniEnd)
	{
		mario.animation.SetClip(mario_Walk);
		
		if (KenBounds.RightBottom.Y >= 0.f)
			mario.transform.position += Vector2::Down * KenMoveSpeed * time.GetDeltatime();
	}
	else
	{
		isUpDown = false;
	}

	if (!isLeftRight && !isUpDown)
		mario.animation.SetClip(mario_Idle);

#ifdef _DEBUG
	//printf("mw_X : %d     mw_Y : %d\n", state.x, state.y); //마우스 좌표 확인용
	Vector2 dir = mario.GetDir(); //오브젝트 방향 확인용
	//printf("{ %.02f , %.02f  }\n", dir.X, dir.Y);
#endif // _DEBUG
}

//랜더링
void MainScene::Rendering()
{
	mario.Rendering();
}
