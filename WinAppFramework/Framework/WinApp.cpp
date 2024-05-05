#include "WinApp.h"
#include "RenderSystem.h"

WinApp WinApp::winApp;

//������ ���� ��ġ�� �� �߾����� ��ġ���ִ� �Լ�
void PlaceInCenterofScreen(HWND window) 
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT clientRect;
	GetClientRect(window, &clientRect);

	int clientWidth = WinApp::GetWinApp().GetClientWidth();
	int clientHeight = WinApp::GetWinApp().GetClientHeight();

	SetWindowPos(window, NULL,
		screenWidth / 2 - clientWidth / 2,
		screenHeight / 2 - clientHeight / 2,
		WinApp::GetWinApp().GetWindowWidth(), WinApp::GetWinApp().GetWindowHeight(), 0
	);
}

//������ api ���� �Լ�
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WinApp::GetWinApp().Initialize(hInstance);

	WinApp::GetWinApp().Run(); //����

	WinApp::GetWinApp().Finalize(); //����

	return EXIT_SUCCESS;
}

void WinApp::Initialize(HINSTANCE hInstance)
{
#ifdef _DEBUG
		AllocConsole();
		FILE* _tempFile;
		freopen_s(&_tempFile, "CONOUT$", "w", stdout);
#endif

	m_hInstance = hInstance;

	const int SCREEN_WIDTH = this->CLIENT_WIDTH;
	const int SCREEN_HEIGHT = this->CLIENT_HEIGHT;
	const TCHAR* appName = TEXT("Win32Framework");

	//Step 1: Registering the Window Class
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);

	// Step 2: Creating the Window
	RECT rect_Client{ 0, 0,
	SCREEN_WIDTH, SCREEN_HEIGHT };

	ClientRectToWindowRect(rect_Client);

	this->WINDOW_WIDTH = abs(rect_Client.left) + abs(rect_Client.right); //���� â ����
	this->WINDOW_HEIGHT = abs(rect_Client.top) + abs(rect_Client.bottom); //���� â ����

	//������ ���� ȭ�� ũ�⿡ ���� ������ â ����
	m_hWnd = CreateWindow(appName, appName, myWndStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	Render::InitRenderSystem();
	GameManager::Gm = &gameManager;	
}

WinApp::WinApp()
{
	
}

WinApp::~WinApp() 
{
	
}

void WinApp::Run()
{
	// Step 4: Game Loop Here
	gameManager.StartGame();
}

void WinApp::Finalize()
{
	// Step 5: Game Finalize Here
	Render::FinalizeRenderSystem();
}

LRESULT CALLBACK WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		PlaceInCenterofScreen(hWnd);
	}
	break;

	case WM_DESTROY:
		GameManager::Gm->EndGame();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void WinApp::ClientRectToWindowRect(RECT& ClientRect) //Ŭ���̾�Ʈ ũ�⸦ ���� ������ ũ��� �ٲ��ִ� �޼���
{
	ClientRect.right += 16;
	ClientRect.bottom += +39;
}