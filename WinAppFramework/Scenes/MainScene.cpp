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
	obj_rect.SetColor(RGB(100, 100, 100)); //�� ����
	obj_rect.SetSquareSize(1000,1000); //ũ�� ����
	obj_rect.transform.position = Vector2{ CLIENT_WIDTH / 2.f , CLIENT_HEIGHT / 2.f }; //��ġ ����

	obj_Sprite.Loadbmp("Resource\\test.bmp"); //���ҽ� �ε�
	obj_Sprite.SetTrColor(RGB(255,255,255)); //���� ����
}

//1�ʿ� time.FixedUpdatePerSec ��ŭ ȣ�� �⺻�� : 50
void MainScene::FixedUpdate()
{
	

}

//�� ������ ȣ��
void MainScene::Update()
{	
	//���콺 �Է�
	input.UpdateMouse();
	Input::MouseState state = input.GetMouseState();

	obj_Sprite.transform.position = Vector2{ state.x, state.y}; //��ġ ����

	obj_Sprite.SetAngle(obj_Sprite.GetAngle() + 30 * time.GetDeltatime()); //�ݽð�� 1�ʿ� 30���� ȸ��

	obj_Sprite.transform.scale += 0.1f * time.GetDeltatime(); //1�ʿ� 10% ũ������

#ifdef _DEBUG
	//printf("mw_X : %d     mw_Y : %d\n", state.x, state.y); //���콺 ��ǥ Ȯ�ο�
	Vector2 dir = obj_Sprite.GetDir();
	printf("{ %.02f , %.02f  }\n", dir.X, dir.Y);
#endif // _DEBUG
}

//������
void MainScene::Rendering()
{
	obj_rect.Rendering();

	obj_Sprite.Rendering();
}
