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
	obj_Ken.Loadbmp("Resource\\Ken\\ken.bmp"); //���ҽ� �ε�
	//obj_Ken.SetAlpha(0.5f); //����
	obj_Ken.SetTrColor(RGB(0,0,168)); //���� ����
	obj_Ken.transform.scale = 2.f;

	//�ִϸ��̼�
	Ken_Idle = obj_Ken.animation.AddClip(L"Resource\\Ken\\KenIdle.txt");
	Ken_Idle->data.frameIntervalTime = 0.15f; //������ ��� �ð� ����

	Ken_Walk = obj_Ken.animation.AddClip(L"Resource\\Ken\\KenMove.txt");

	Ken_Attack = obj_Ken.animation.AddClip(L"Resource\\Ken\\KenAttack.txt", false);
	Ken_Attack->data.frameIntervalTime = 0.08f;

	obj_Ken.animation.SetClip(Ken_Idle); //�⺻ ����� Ŭ�� ����
	obj_Ken.transform.position = Vector2{ CLIENT_WIDTH / 2.f, CLIENT_HEIGHT / 2.f };

	//�̹��� ���� ����
	obj_Ken.Flip_X = false;
	obj_Ken.Flip_Y = false;

}

//1�ʿ� time.FixedUpdatePerSec ��ŭ ȣ�� �⺻�� : 50
void MainScene::FixedUpdate()
{
	

}

//�� ������ ȣ��
void MainScene::Update()
{	
	//�ִϸ��̼� ������Ʈ
	obj_Ken.animation.UpdateFrmae(time.GetDeltatime()); 

	//Ű���� �Է�
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
	//printf("mw_X : %d     mw_Y : %d\n", state.x, state.y); //���콺 ��ǥ Ȯ�ο�
	Vector2 dir = obj_Ken.GetDir(); //������Ʈ ���� Ȯ�ο�
	printf("{ %.02f , %.02f  }\n", dir.X, dir.Y);
#endif // _DEBUG
}

//������
void MainScene::Rendering()
{
	obj_Ken.Rendering();
}
