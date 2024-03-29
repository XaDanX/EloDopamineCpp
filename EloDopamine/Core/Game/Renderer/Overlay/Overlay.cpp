#include "Overlay.h"
#include <dcomp.h>
#include <d3d11.h>
#include "../Renderer.h"
#include "../../../Utils/StringUtils.h"
#include "../../../Security/XorStr.hpp"

ID3D11Device* Overlay::dxDevice = NULL;
ID3D11DeviceContext* Overlay::dxDeviceContext = NULL;
IDXGISwapChain1* Overlay::dxSwapChain = NULL;
ID3D11RenderTargetView* Overlay::dxRenderTarget = NULL;

Overlay::Overlay(){
}

void Overlay::SetupStyle() {
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
}


void Overlay::Init() {
	std::string windowClassName = RandomString(11);
	std::string windowName = RandomString(11);
	SetConsoleTitleA(windowName.c_str());

	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, windowClassName.c_str(), NULL };
	RegisterClassExA(&wc);
	hWindow = CreateWindowExA(
		WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED,
		windowClassName.c_str(), windowName.c_str(),
		WS_POPUP,
		1, 1, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
		nullptr, nullptr, GetModuleHandle(0), nullptr);

	if (hWindow == nullptr) {
		return;
	}

	SetWindowLong(hWindow, GWL_STYLE, 0);
	ShowWindow(hWindow, SW_SHOW);


	if (!CreateDeviceD3D(hWindow))
	{
		CleanupDeviceD3D();
		throw std::runtime_error(XorStr("Failed to create D3D device"));
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.IniFilename = nullptr;


	io.Fonts->AddFontFromFileTTF(XorStr("C:\\Deployable\\Font.ttf").c_str(), 16.0f);
	Fonts::font11 = io.Fonts->AddFontFromFileTTF(XorStr("C:\\Deployable\\Font.ttf").c_str(), 11.0f);
	Fonts::font19 = io.Fonts->AddFontFromFileTTF(XorStr("C:\\Deployable\\Font.ttf").c_str(), 22.0f);
	this->SetupStyle();


	ImGui_ImplWin32_Init(hWindow);
	ImGui_ImplDX11_Init(dxDevice, dxDeviceContext);

	ImGui::GetStyle().Alpha = 1.f;
}


void Overlay::StartFrame()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Overlay::Update() {

}

void Overlay::RenderFrame()
{
	static ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 0.f);

	ImGui::EndFrame();
	ImGui::Render();
	dxDeviceContext->OMSetRenderTargets(1, &dxRenderTarget, NULL);
	dxDeviceContext->ClearRenderTargetView(dxRenderTarget, (float*)&clear_color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	dxSwapChain->Present(0, 0);

}


bool Overlay::IsVisible()
{
	return isWindowVisible;
}

void Overlay::Hide()
{
	ShowWindow(hWindow, SW_HIDE);
	isWindowVisible = false;
}

void Overlay::Show()
{
	ShowWindow(hWindow, SW_SHOW);
	isWindowVisible = true;
}

void Overlay::ToggleTransparent()
{
	LONG ex_style = GetWindowLong(hWindow, GWL_EXSTYLE);
	ex_style = (ex_style & WS_EX_TRANSPARENT) ? (ex_style & ~WS_EX_TRANSPARENT) : (ex_style | WS_EX_TRANSPARENT);
	SetWindowLong(hWindow, GWL_EXSTYLE, ex_style);
}

ID3D11Device* Overlay::GetDxDevice()
{
	return dxDevice;
}

bool Overlay::CreateDeviceD3D(HWND hWnd)
{
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	D3D11CreateDevice(
		nullptr,   
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		nullptr, 0, 
		D3D11_SDK_VERSION,
		&dxDevice,
		nullptr,   
		&dxDeviceContext);

	IDXGIDevice3* dxgiDevice;
	dxDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	IDXGIFactory2* dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);

	DXGI_SWAP_CHAIN_DESC1 description = {};
	description.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	description.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	description.BufferCount = 6;
	description.SampleDesc.Count = 1;
	description.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
	description.Scaling = DXGI_SCALING_STRETCH;
	RECT rect = {};
	GetClientRect(hWnd, &rect);
	description.Width = rect.right - rect.left;
	description.Height = rect.bottom - rect.top;

	dxgiFactory->CreateSwapChainForComposition(dxgiDevice,
		&description,
		nullptr,
		&dxSwapChain);

	dxgiDevice->SetMaximumFrameLatency(2);
	dxgiDevice->SetGPUThreadPriority(7);
	
	IDCompositionDevice* dcompDevice;
	DCompositionCreateDevice(
		dxgiDevice,
		__uuidof(dcompDevice),
		(void**)&dcompDevice);

	IDCompositionTarget* target;
	dcompDevice->CreateTargetForHwnd(hWnd,
		true,
		&target);

	IDCompositionVisual* visual;
	dcompDevice->CreateVisual(&visual);
	visual->SetContent(dxSwapChain);
	target->SetRoot(visual);
	dcompDevice->Commit();
	

	CreateRenderTarget();
	return true;
}

void Overlay::CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (dxSwapChain) { dxSwapChain->Release(); dxSwapChain = NULL; }
	if (dxDeviceContext) { dxDeviceContext->Release(); dxDeviceContext = NULL; }
	if (dxDevice) { dxDevice->Release(); dxDevice = NULL; }
}

void Overlay::CreateRenderTarget()
{
	ID3D11Resource* pBackBuffer;
	if (S_OK != dxSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)))
		throw std::runtime_error(XorStr("Failed to retrieve DX11 swap chain buffer"));
	if (S_OK != dxDevice->CreateRenderTargetView(pBackBuffer, NULL, &dxRenderTarget))
		throw std::runtime_error(XorStr("Failed to create DX11 render target"));
	pBackBuffer->Release();
}

void Overlay::CleanupRenderTarget()
{
	if (dxRenderTarget) { dxRenderTarget->Release(); dxRenderTarget = NULL; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI Overlay::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (dxDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			dxSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
