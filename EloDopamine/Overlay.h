#pragma once

#include <chrono>
#include <map>
#include <list>

#include "windows.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include <dinput.h>
#include <dxgi1_3.h>
#include <d3d11_2.h>
#include <dcomp.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment( lib, "dcomp" )


class Overlay {

public:
	Overlay();
	void                  Init();

	void                  StartFrame();
	void                  Update();
	void                  RenderFrame();

	bool                  IsVisible();
	void                  Hide();
	void                  Show();
	void                  ToggleTransparent();

	static ID3D11Device* GetDxDevice();


private:

	static bool    CreateDeviceD3D(HWND hWnd);
	static void    CleanupDeviceD3D();
	static void    CreateRenderTarget();
	static void    CleanupRenderTarget();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void SetupStyle();


private:
	HWND                               hWindow;
	bool                               isWindowVisible = true;

	static ID3D11Device* dxDevice;
	static ID3D11DeviceContext* dxDeviceContext;
	static IDXGISwapChain1* dxSwapChain;
	static ID3D11RenderTargetView* dxRenderTarget;
};

