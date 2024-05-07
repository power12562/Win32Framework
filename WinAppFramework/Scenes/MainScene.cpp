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
	obj_Ken.Loadbmp("Resource\\Ken\\ken.bmp"); //리소스 로드
	//obj_Ken.SetAlpha(0.5f); //투명도
	obj_Ken.SetTrColor(RGB(0,0,168)); //배경색 제거
	obj_Ken.transform.scale = 2.f;

	//애니메이션
	Ken_Idle = obj_Ken.animation.AddClip(L"Resource\\Ken\\KenIdle.txt");
	Ken_Idle->data.frameIntervalTime = 0.15f; //프레임 재생 시간 간격

	Ken_Walk = obj_Ken.animation.AddClip(L"Resource\\Ken\\KenMove.txt");

	Ken_Attack = obj_Ken.animation.AddClip(L"Resource\\Ken\\KenAttack.txt", false);
	Ken_Attack->data.frameIntervalTime = 0.08f;

	obj_Ken.animation.SetClip(Ken_Idle); //기본 재생할 클립 설정
	obj_Ken.transform.position = Vector2{ CLIENT_WIDTH / 2.f, CLIENT_HEIGHT / 2.f };

	//이미지 반전 여부
	obj_Ken.Flip_X = false;
	obj_Ken.Flip_Y = false;

}

//1초에 time.FixedUpdatePerSec 만큼 호출 기본값 : 50
void MainScene::FixedUpdate()
{
	

}

//매 프레임 호출
void MainScene::Update()
{	
	//애니메이션 업데이트
	obj_Ken.animation.UpdateFrmae(time.GetDeltatime()); 

	//키보드 입력
	bool isLeftRight = true;
	bool isUpDown = true;
	bool isAniEnd = obj_Ken.animation.IsClipEnd();
	if (input.IsKey(KeyCode::RightArrow) && isAniEnd)
	{
		obj_Ken.animation.SetClip(Ken_Walk);
		obj_Ken.transform.position += obj_Ken.GetDir() * KenMoveSpeed * time.GetDeltatime();
		obj_Ken.Flip_X = false;
	}
	else if (input.IsKey(KeyCode::LeftArrow) && isAniEnd)
	{
		obj_Ken.animation.SetClip(Ken_Walk);
		obj_Ken.transform.position -= obj_Ken.GetDir() * KenMoveSpeed * time.GetDeltatime();
		obj_Ken.Flip_X = true;
	}
	else
	{
		isLeftRight = false;
	}

	if (input.IsKey(KeyCode::UpArrow) && isAniEnd)
	{
		obj_Ken.animation.SetClip(Ken_Walk);

		obj_Ken.transform.position += Vector2::Up * KenMoveSpeed * time.GetDeltatime();
	}
	else if (input.IsKey(KeyCode::DownArrow) && isAniEnd)
	{
		obj_Ken.animation.SetClip(Ken_Walk);
		
		obj_Ken.transform.position += Vector2::Down * KenMoveSpeed * time.GetDeltatime();
	}
	else
	{
		isUpDown = false;
	}

	if (input.IsKeyDown(KeyCode::Space))
	{
		obj_Ken.animation.SetClip(Ken_Attack);
	}

	if (!isLeftRight && !isUpDown)
		obj_Ken.animation.SetClip(Ken_Idle);


#ifdef _DEBUG
	//printf("mw_X : %d     mw_Y : %d\n", state.x, state.y); //마우스 좌표 확인용
	Vector2 dir = obj_Ken.GetDir(); //오브젝트 방향 확인용
	printf("{ %.02f , %.02f  }\n", dir.X, dir.Y);
#endif // _DEBUG
}

//랜더링
void MainScene::Rendering()
{
	obj_Ken.Rendering();
}
