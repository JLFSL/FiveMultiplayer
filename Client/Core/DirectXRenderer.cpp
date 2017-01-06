#include "stdafx.h"

DirectXRenderer* DirectXRenderer::Instance = nullptr;

DirectXRenderer::DirectXRenderer()
{
	Instance = this;

	FirstRender = true;
}

DirectXRenderer::~DirectXRenderer()
{
	Instance = nullptr;
}

bool show_app_about = true;

HRESULT WINAPI Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	DirectXRenderer *curInstance = DirectXRenderer::GetInstance();

	if (DirectXRenderer::GetInstance()->FirstRender)
	{
		pSwapChain->GetDevice(__uuidof(curInstance->pDevice), (void**)&curInstance->pDevice);
		curInstance->pDevice->GetImmediateContext(&curInstance->pContext);

		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChain->GetDesc(&sd);

		// Create the render target
		ID3D11Texture2D* pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
		ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
		render_target_view_desc.Format = sd.BufferDesc.Format;
		render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		curInstance->pDevice->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &curInstance->phookD3D11RenderTargetView);
		curInstance->pContext->OMSetRenderTargets(1, &curInstance->phookD3D11RenderTargetView, NULL);
		pBackBuffer->Release();

		FW1CreateFactory(FW1_VERSION, &curInstance->pFW1Factory);
		curInstance->pFW1Factory->CreateFontWrapper(curInstance->pDevice, L"Segoe UI", &curInstance->pFontWrapper);
		curInstance->pFW1Factory->Release();

		DirectXDraw::GetInstance()->Initialize();

		ImGui_ImplDX11_Init(curInstance->hWnd, curInstance->pDevice, curInstance->pContext);
		ImGui_ImplDX11_CreateDeviceObjects();

		DirectXRenderer::GetInstance()->FirstRender = false;
	}

	float fontsize = 24.0f;

	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 34.0f, 32.0f, 0xff000000, FW1_RESTORESTATE);
	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 30.0f, 32.0f, 0xff000000, FW1_RESTORESTATE);

	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 32.0f, 34.0f, 0xff000000, FW1_RESTORESTATE);
	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 32.0f, 30.0f, 0xff000000, FW1_RESTORESTATE);

	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 34.0f, 34.0f, 0xff000000, FW1_RESTORESTATE);
	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 30.0f, 30.0f, 0xff000000, FW1_RESTORESTATE);

	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 34.0f, 30.0f, 0xff000000, FW1_RESTORESTATE);
	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 30.0f, 34.0f, 0xff000000, FW1_RESTORESTATE);

	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", fontsize, 32.0f, 32.0f, 0xffffffff, FW1_RESTORESTATE);

	ImGui_ImplDX11_NewFrame();

	if (show_app_about)
	{
		ImGui::Begin("About ImGui", &show_app_about, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("dear imgui, %s", ImGui::GetVersion());
		ImGui::Separator();
		ImGui::Text("By Omar Cornut and all github contributors.");
		ImGui::Text("ImGui is licensed under the MIT License, see LICENSE for more information.");
		ImGui::End();
	}

	//DirectXDraw::GetInstance()->BeginScene();
	///DirectXDraw::GetInstance()->DrawScene();
	//DirectXDraw::GetInstance()->EndScene();

	ImGui::Render();

	return DirectXRenderer::GetInstance()->phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

void DirectXRenderer::Initialize()
{
	hWnd = FindWindowA(NULL, "Grand Theft Auto V");
	IDXGISwapChain* pSwapChain;

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0};
	D3D_FEATURE_LEVEL obtainedLevel;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.Width = 1;
	swapChainDesc.BufferDesc.Height = 1;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, NULL, featureLevel, sizeof(featureLevel) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, &obtainedLevel, &pContext)))
	{
		MessageBoxA(hWnd, "Failed to load FiveMP with DirectX, make sure your game is using DirectX 11, 10.1 or 10!", "FiveMP", MB_ICONERROR);
		return;
	}

	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pDeviceContextVTable = (DWORD_PTR*)pContext;
	pDeviceContextVTable = (DWORD_PTR*)pDeviceContextVTable[0];

	if (MH_Initialize() != MH_OK) {
		Logger::Error("Failed to initialize hook");
		return;
	}
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[8], Present, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) {
		Logger::Error("Failed to create directx hook");
		return;
	}
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) {
		Logger::Error("Failed to enable directx hook");
		return;
	}

	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();
}