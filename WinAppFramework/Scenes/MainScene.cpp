#include "MainScene.h"
#include "..\Framework\WinApp.h"
MainScene::MainScene()
{
	CLIENT_WIDTH = WinApp::GetWinApp().GetClientWidth();
	CLIENT_HEIGHT = WinApp::GetWinApp().GetClientHeight();
}

//�� ���۽� 1ȸ ����
void MainScene::Start()
{
	mario.Loadbmp("Resource\\mario\\mario.bmp"); //���ҽ� �ε�
	//obj_Ken.SetAlpha(0.5f); //����
	mario.SetTrColor(RGB(153,217,234)); //���� ����
	mario.transform.scale = { 5.f, 5.f };

	//�ִϸ��̼�
	mario_Idle = mario.animation.AddClip(L"Resource\\mario\\Idle.txt");
	mario_Idle->data.frameIntervalTime = 0.02f; //������ ��� �ð� ����

	mario_Walk = mario.animation.AddClip(L"Resource\\mario\\Walk.txt");
	mario_Walk->data.frameIntervalTime = 0.02f;

	mario.animation.SetClip(mario_Idle); //�⺻ ����� Ŭ�� ����
	mario.transform.position = Vector2{ CLIENT_WIDTH / 2.f, CLIENT_HEIGHT / 2.f };

	//�̹��� ���� ����
	mario.Flip_X = false;
	mario.Flip_Y = false;
}

//1�ʿ� time.FixedUpdatePerSec ��ŭ ȣ�� �⺻�� : 50
void MainScene::FixedUpdate()
{
	

}

//�� ������ ȣ��
void MainScene::Update()
{	
	//�ִϸ��̼� ������Ʈ
	mario.animation.UpdateFrmae(time.GetDeltatime()); 

	//Ű���� �Է�
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
	//printf("mw_X : %d     mw_Y : %d\n", state.x, state.y); //���콺 ��ǥ Ȯ�ο�
	Vector2 dir = mario.GetDir(); //������Ʈ ���� Ȯ�ο�
	//printf("{ %.02f , %.02f  }\n", dir.X, dir.Y);
#endif // _DEBUG
}

//������
void MainScene::Rendering()
{
	mario.Rendering();
}
