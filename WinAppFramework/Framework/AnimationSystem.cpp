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

	//클립 파일 불러온다.
	wifstream file(fileName);
	if (!file.is_open()) {
		cout << "파일 경로 확인 해주세요." << endl;
		throw;
	}
	wstring line;			// 한줄의 문자열	
	Clip newClip;
	My::List<Animation::Clip>::Node* pNode = ClipList.PushBack(newClip); //클립 생성
	Clip& clip = pNode->data;
	{
		getline(file, line);		// 첫번째 줄 (프레임 수) 읽기
		wstringstream wss(line);
		wss >> clip.FrameCount;
		clip.Frames = new Frame[clip.FrameCount]; //동적 할당
	}
	//클립 정보 저장
	for (int j = 0; j < clip.FrameCount; j++)
	{
		getline(file, line);		// 한줄 읽기
		wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
		wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
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
	
	//노드 포인터 반환	
	return pNode;
}

//재생할 애니메이션 클립 설정
void Animation::SetClip(My::List<Animation::Clip>::Node* clip)
{
	if (CurrentClip != &(clip->data) && isCurrentClipEnd)
	{
		CurrentClip = &(clip->data);
		isCurrentClipEnd = (CurrentClip->IsLoop) ? true : false;
		CurrentFrame = 0;
	}
}

//애니메이션 클립 삭제
void Animation::DelClip(My::List<Animation::Clip>::Node* clip)
{
	if (CurrentClip == &(clip->data))
	{
		CurrentClip = nullptr;
	}
	ClipList.Erase(clip);	
}


//델타 타임에 따라 프레임이 자동으로 변경된다.
void Animation::UpdateFrmae(float DeltaTime)
{
	if (CurrentClip == nullptr) return;

	elapsedTime += DeltaTime;
	while (elapsedTime >= CurrentClip->frameIntervalTime) //시간 도달하면 다음 프레임으로 변경
	{
		CurrentFrame++;
		elapsedTime -= CurrentClip->frameIntervalTime;
	}
	if (CurrentFrame == CurrentClip->FrameCount)
	{
		if (CurrentClip->IsLoop == true)
			CurrentFrame = 0; //루프
		else
		{
			CurrentFrame--;
			isCurrentClipEnd = true;
		}
	}
}