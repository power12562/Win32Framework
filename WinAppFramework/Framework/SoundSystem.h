#pragma once
#include <Windows.h>
#include <mmsystem.h>            
#include <Digitalv.h>      

#pragma comment (lib, "winmm.lib")   

class Sound
{
public:
	Sound();
	Sound(const wchar_t* path);
	~Sound();
	void SetFilePath(const wchar_t* path);
	void SetType_Wav();
	void SetType_Mpeg();
	void Play();
	void Stop();
	bool isLoop = false;

private:
	// MediaPlayer °´Ã¼
	DWORD dwID;
	MCI_OPEN_PARMS mciOpen;
	wchar_t* m_path;
	void DeleteInstance();
};
