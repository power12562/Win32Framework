#pragma once
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

class WinApp
{
public:

	WinApp();	
	~WinApp();	

	void Initialize(HINSTANCE hInstance);

	void Run();

	void Finalize();

	HINSTANCE GetInstance() const { return m_hInstance; }

	HWND GetWindow() const { return m_hWnd; }

	const int GetClientWidth() const { return CLIENT_WIDTH; }
	const int GetClientHeight() const { return CLIENT_HEIGHT; }

	const int GetWindowWidth() const { return WINDOW_WIDTH; }
	const int GetWindowHeight() const { return WINDOW_HEIGHT; }

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //���ν���

	static WinApp& GetWinApp() { return winApp; }

private:

	static WinApp winApp;

	HINSTANCE m_hInstance = { 0 };
	HWND m_hWnd = { 0 };
	
	int WINDOW_WIDTH = 0; //���� â ����
	int WINDOW_HEIGHT = 0; //���� â ����

	const DWORD myWndStyle = WS_OVERLAPPED | WS_SYSMENU;

	const int CLIENT_WIDTH = 1920;
	const int CLIENT_HEIGHT = 1080;

	void ClientRectToWindowRect(RECT& ClientRect); //Ŭ���̾�Ʈ ũ�⸦ ���� ������ ũ��� �ٲ��ִ� �޼���
};
