#include <Windows.h>
#include <stdio.h>
#include "Graphics.h"
#include "Level1.h"
#include "Level0.h"
#include "GameController.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

Graphics* graphics;
Level0* level0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}

	switch (uMsg)
	{
	case WM_KEYDOWN: // A >> 0x41, S >> 0x53, D >> 0x44, W >> 0x53
		/*if (wParam == 0x53) {
			level1->MoveDown();
		}*/
		
		if (wParam == 0x57) {
			GameController::GetCurrentLevel()->MoveUp();
		}

		if (wParam == 0x41) {
			GameController::GetCurrentLevel()->MoveLeft();
		}

		if (wParam == 0x44) {
			GameController::GetCurrentLevel()->MoveRight();
		}

		if (wParam == VK_SPACE) {
			GameController::GetCurrentLevel()->Jump();
		}

		break;
	case WM_KEYUP:
		/*if (wParam == 0x53) {
			level1->StopDown();
		}*/

		/*if (wParam == 0x57) {
			level1->StopUp();
		}*/

		if (wParam == 0x41) {
			GameController::GetCurrentLevel()->StopLeft();
		}

		if (wParam == 0x44) {
			GameController::GetCurrentLevel()->StopRight();
		}

		break;
	case WM_LBUTTONDOWN:
		GameController::GetCurrentLevel()->MouseDown(hwnd);
		break;
	case WM_LBUTTONUP:
		GameController::GetCurrentLevel()->MouseUp();
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {

	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	RECT rect = { 0,0,1280, 720 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Dungreed", WS_OVERLAPPEDWINDOW,
		500, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowhandle) {
		return -1;
	}

	graphics = new Graphics();
	if (!graphics->Init(windowhandle)) {
		delete graphics;
		return -1;
	}

	GameLevel::Init(graphics);

	ShowWindow(windowhandle, nCmdShow);

	GameController::Init();
	level0 = new Level0();
	GameController::LoadInitialLevel(level0);

	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT) {
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&message);
		}
		else {
			GameController::Update();

			// ·»´õ¸µ
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();
		}
	}

	/*MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		DispatchMessage(&message);
	}*/

	delete graphics;

	return 0;
}