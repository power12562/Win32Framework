#pragma once
#include "DataType/MyList.h"
#include "windows.h" //WCHAR, RECT 용

class Animation
{	
public:
	Animation();
	~Animation() { ClipList.Clear(); }

	// 동작의 하나의 프레임 정보
	struct Frame
	{
		RECT Source = { 0, };	// 부분출력할 이미지 영역
		SIZE Size = { 0, };		// 출력 크기
		int CenterX = 0, CenterY = 0;	// 중심이 되는 이동 위치 
	};
	class Clip //애니메이션 클립
	{
	public:
		~Clip() { delete[] Frames; }
		Frame* Frames = nullptr; //프레임 컨테이너
		int FrameCount = 0;			// 전체 프레임 수
		bool IsLoop = false;	// 반복 여부
		float frameIntervalTime = 0.1f; //해당 클립의 프레임 간격 시간
	};
	My::List<Clip>::Node* AddClip(const WCHAR* fileName, bool IsLoop = true); //애니메이션 클립 추가
	void SetClip(My::List<Clip>::Node* clip); //재생할 클립 선택
	void DelClip(My::List<Clip>::Node* clip); //클립 삭제
	virtual void UpdateFrmae(float DeltaTime);
	Clip* GetCurrClip() { return CurrentClip; }
	const Frame& GetCurrentFrame() const { return CurrentClip->Frames[CurrentFrame]; }
	bool IsClipEnd() { return isCurrentClipEnd; }

protected:
	My::List<Clip> ClipList; //클립 리스트
	Clip* CurrentClip = nullptr; //현재 선택된 클립

	int CurrentFrame = 0; //현재 재생중인 프레임
	bool isCurrentClipEnd = true; //현재 재생중인 클립 끝낫는지
	float elapsedTime = 0; //애니메이션 진행 시간
};