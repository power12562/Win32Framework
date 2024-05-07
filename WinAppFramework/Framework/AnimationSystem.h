#pragma once
#include "DataType/MyList.h"
#include "windows.h" //WCHAR, RECT ��

class Animation
{	
public:
	Animation();
	~Animation() { ClipList.Clear(); }

	// ������ �ϳ��� ������ ����
	struct Frame
	{
		RECT Source = { 0, };	// �κ������ �̹��� ����
		SIZE Size = { 0, };		// ��� ũ��
		int CenterX = 0, CenterY = 0;	// �߽��� �Ǵ� �̵� ��ġ 
	};
	class ClipClass //�ִϸ��̼� Ŭ��
	{
	public:
		~ClipClass() { delete[] Frames; }
		Frame* Frames = nullptr; //������ �����̳�
		int FrameCount = 0;			// ��ü ������ ��
		bool IsLoop = false;	// �ݺ� ����
		float frameIntervalTime = 0.1f; //�ش� Ŭ���� ������ ���� �ð�
	};
	typedef My::List<Animation::ClipClass>::Node* Clip;

	Clip AddClip(const WCHAR* fileName, bool IsLoop = true); //�ִϸ��̼� Ŭ�� �߰�
	void SetClip(My::List<ClipClass>::Node* clip); //����� Ŭ�� ����
	void DelClip(My::List<ClipClass>::Node* clip); //Ŭ�� ����
	virtual void UpdateFrmae(float DeltaTime);
	ClipClass* GetCurrClip() { return CurrentClip; }
	const Frame& GetCurrentFrame() const { return CurrentClip->Frames[CurrentFrame]; }
	bool IsClipEnd() { return isCurrentClipEnd; }

protected:
	My::List<ClipClass> ClipList; //Ŭ�� ����Ʈ
	ClipClass* CurrentClip = nullptr; //���� ���õ� Ŭ��

	int CurrentFrame = 0; //���� ������� ������
	bool isCurrentClipEnd = true; //���� ������� Ŭ�� ��������
	float elapsedTime = 0; //�ִϸ��̼� ���� �ð�
};