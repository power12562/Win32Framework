#include "SoundSystem.h"
#include <wchar.h>

Sound::Sound()
{
	mciOpen = { 0, };
	dwID = NULL;
	m_path = nullptr;
}

Sound::Sound(const wchar_t* path)
{
	SetType_Wav(); //기본 설정은 wav
	SetFilePath(path);
	
}

Sound::~Sound()
{
	DeleteInstance();

	delete[] m_path;
}

void Sound::SetFilePath(const wchar_t* path)
{
	DeleteInstance();

	size_t size = wcslen(path) + 1;
	if (m_path != nullptr)
	{
		delete[] m_path;
	}	
	m_path = new wchar_t[size];
	swprintf_s(m_path, size, path);


	mciOpen.lpstrElementName = m_path;
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&mciOpen);
	dwID = mciOpen.wDeviceID;
}

void Sound::SetType_Wav()
{
	mciOpen.lpstrDeviceType = L"waveaudio";
}

void Sound::SetType_Mpeg()
{
	mciOpen.lpstrDeviceType = L"mpegvideo";
}

void Sound::Play()
{
	// 음악 재생
	MCI_PLAY_PARMS mciPlayParms;
	if (isLoop)
	{		
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&mciPlayParms); //루프
	}
	else
	{
		mciSendCommand(dwID, MCI_PLAY, 0, (DWORD_PTR)&mciPlayParms);
	}
}

void Sound::Stop()
{
	// 재생 중지 및 처음으로
	MCI_GENERIC_PARMS mciGenericParms;
	mciSendCommand(dwID, MCI_STOP, 0, (DWORD_PTR)&mciGenericParms);
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&mciGenericParms);
}

void Sound::DeleteInstance()
{
	if (dwID != NULL)
	{
		MCI_GENERIC_PARMS mciGenericParms;
		mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD_PTR)&mciGenericParms);

		dwID = NULL;
	}
}