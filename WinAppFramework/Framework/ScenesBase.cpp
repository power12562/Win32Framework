#include "ScenesBase.h"
#include "RenderSystem.h"
#include <stdio.h>

SceneBase::SceneBase(int FixedUpdateToSec)
{
	isGameEnd = false;
	time.FixedUpdatePerSec = FixedUpdateToSec;
	FixedUpdate_elapsedTime = 0;
}

SceneBase::~SceneBase()
{
	
}

void SceneBase::GameRun()
{
	time.UpdateTime(); //deltaTime 초기화 위해서 한번 호출
	Start();	
	MSG msg;
	while (!isGameEnd)
	{	
		// GetMessage 가 아니라 PeekMessage 를 사용합니다!!
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			if (msg.message == WM_KEYDOWN && !input.IsKey(static_cast<KeyCode>(msg.wParam)))
			{
				input.KeyDown(static_cast<KeyCode>(msg.wParam));
			}
			else if (msg.message == WM_KEYUP && input.IsKey(static_cast<KeyCode>(msg.wParam)))
			{
				input.KeyUp(static_cast<KeyCode>(msg.wParam));
			}
			else
			{
				DispatchMessage(&msg);
			}
		}
		else 
		{
			time.UpdateTime();
			
			//FixedUpdate는 초당 일정 횟수를 보장 받는다.
			{		
				const float FixedUpdateTimeMs = (float)1000.f / (float)time.FixedUpdatePerSec;
				FixedUpdate_elapsedTime += time.GetDeltatime_ms();
				while (FixedUpdate_elapsedTime >= FixedUpdateTimeMs)
				{
					FixedUpdate();
					FixedUpdate_elapsedTime -= FixedUpdateTimeMs;
				}
			}
		
			Update();

			Render::BeginDraw();
			Rendering();
			Render::EndDraw();

			input.ResetInput();
		}
	}
}

void SceneBase::Finalize()
{
	isGameEnd = true;
}

