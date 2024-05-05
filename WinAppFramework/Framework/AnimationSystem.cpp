#include "AnimationSystem.h"

#include <iostream>
#include <fstream>
#include <sstream>

Animation::Animation()
{

}

My::List<Animation::Clip>::Node* Animation::AddClip(const WCHAR* fileName, bool IsLoop)
{
	using namespace std;

	//Ŭ�� ���� �ҷ��´�.
	wifstream file(fileName);
	if (!file.is_open()) {
		cout << "���� ��� Ȯ�� ���ּ���." << endl;
		throw;
	}
	wstring line;			// ������ ���ڿ�	
	Clip newClip;
	My::List<Animation::Clip>::Node* pNode = ClipList.PushBack(newClip); //Ŭ�� ����
	Clip& clip = pNode->data;
	{
		getline(file, line);		// ù��° �� (������ ��) �б�
		wstringstream wss(line);
		wss >> clip.FrameCount;
		clip.Frames = new Frame[clip.FrameCount]; //���� �Ҵ�
	}
	//Ŭ�� ���� ����
	for (int j = 0; j < clip.FrameCount; j++)
	{
		getline(file, line);		// ���� �б�
		wstringstream wss(line);    // ������ �о wstringstream�� ����
		wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
			clip.Frames[j].Source.left = _wtoi(token.c_str());
			getline(wss, token, L',');
			clip.Frames[j].Source.top = _wtoi(token.c_str());
			getline(wss, token, L',');
			clip.Frames[j].Source.right = _wtoi(token.c_str());
			getline(wss, token, L',');
			clip.Frames[j].Source.bottom = _wtoi(token.c_str());
			getline(wss, token, L',');
			clip.Frames[j].CenterX = _wtoi(token.c_str());
			getline(wss, token, L',');
			clip.Frames[j].CenterY = _wtoi(token.c_str());

			clip.Frames[j].Size.cx = clip.Frames[j].Source.right - clip.Frames[j].Source.left + 1;
			clip.Frames[j].Size.cy = clip.Frames[j].Source.bottom - clip.Frames[j].Source.top + 1;
		}
	}
	clip.IsLoop = IsLoop;
	
	//��� ������ ��ȯ	
	return pNode;
}

//����� �ִϸ��̼� Ŭ�� ����
void Animation::SetClip(My::List<Animation::Clip>::Node* clip)
{
	if (CurrentClip != &(clip->data) && isCurrentClipEnd)
	{
		CurrentClip = &(clip->data);
		isCurrentClipEnd = (CurrentClip->IsLoop) ? true : false;
		CurrentFrame = 0;
	}
}

//�ִϸ��̼� Ŭ�� ����
void Animation::DelClip(My::List<Animation::Clip>::Node* clip)
{
	if (CurrentClip == &(clip->data))
	{
		CurrentClip = nullptr;
	}
	ClipList.Erase(clip);	
}


//��Ÿ Ÿ�ӿ� ���� �������� �ڵ����� ����ȴ�.
void Animation::UpdateFrmae(float DeltaTime)
{
	if (CurrentClip == nullptr) return;

	elapsedTime += DeltaTime;
	while (elapsedTime >= CurrentClip->frameIntervalTime) //�ð� �����ϸ� ���� ���������� ����
	{
		CurrentFrame++;
		elapsedTime -= CurrentClip->frameIntervalTime;
	}
	if (CurrentFrame == CurrentClip->FrameCount)
	{
		if (CurrentClip->IsLoop == true)
			CurrentFrame = 0; //����
		else
		{
			CurrentFrame--;
			isCurrentClipEnd = true;
		}
	}
}