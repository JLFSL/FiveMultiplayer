#include "stdafx.h"

// class inits to prevent LNK2001
HWND DirectXRenderer::hWnd = nullptr;
bool DirectXRenderer::FirstRender = true;

ID3D11Device *DirectXRenderer::pDevice = nullptr;
ID3D11DeviceContext *DirectXRenderer::pContext = nullptr;
IDXGISwapChain* DirectXRenderer::pSwapChain = nullptr;

IFW1Factory *DirectXRenderer::pFW1Factory = nullptr;
IFW1FontWrapper *DirectXRenderer::pFontWrapper = nullptr;

DirectXRenderer::D3D11PresentHook DirectXRenderer::phookD3D11Present = nullptr;
DirectXRenderer::D3D11DrawIndexedHook DirectXRenderer::phookD3D11DrawIndexed = nullptr;
DirectXRenderer::D3D11ClearRenderTargetViewHook DirectXRenderer::phookD3D11ClearRenderTargetView = nullptr;
ID3D11RenderTargetView* DirectXRenderer::phookD3D11RenderTargetView = nullptr;

DWORD_PTR* DirectXRenderer::pSwapChainVtable = nullptr;
DWORD_PTR* DirectXRenderer::pDeviceContextVTable = nullptr;

bool show_app_about = true;

HRESULT WINAPI Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (DirectXRenderer::FirstRender)
	{
		pSwapChain->GetDevice(__uuidof(DirectXRenderer::pDevice), (void**)&DirectXRenderer::pDevice);
		DirectXRenderer::pDevice->GetImmediateContext(&DirectXRenderer::pContext);

		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChain->GetDesc(&sd);

		// Create the render target
		ID3D11Texture2D* pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
		ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
		render_target_view_desc.Format = sd.BufferDesc.Format;
		render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		DirectXRenderer::pDevice->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &DirectXRenderer::phookD3D11RenderTargetView);
		DirectXRenderer::pContext->OMSetRenderTargets(1, &DirectXRenderer::phookD3D11RenderTargetView, NULL);
		pBackBuffer->Release();

		FW1CreateFactory(FW1_VERSION, &DirectXRenderer::pFW1Factory);
		DirectXRenderer::pFW1Factory->CreateFontWrapper(DirectXRenderer::pDevice, L"Segoe UI", &DirectXRenderer::pFontWrapper);
		DirectXRenderer::pFW1Factory->Release();

		//DirectXDraw::GetInstance()->Initialize();

		ImGui_ImplDX11_Init(DirectXRenderer::hWnd, DirectXRenderer::pDevice, DirectXRenderer::pContext);
		ImGui_ImplDX11_CreateDeviceObjects();
		
		if (!CefTexture::SetupD3D())
			std::cout << "setup cef d3d texture failed" << std::endl;

		DirectXRenderer::FirstRender = false;
	}

	/*float fontsize = 24.0f;

	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 34.0f, 32.0f, 0xff000000, FW1_RESTORESTATE);
	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 30.0f, 32.0f, 0xff000000, FW1_RESTORESTATE);

	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 32.0f, 34.0f, 0xff000000, FW1_RESTORESTATE);
	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 32.0f, 30.0f, 0xff000000, FW1_RESTORESTATE);

	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 34.0f, 34.0f, 0xff000000, FW1_RESTORESTATE);
	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 30.0f, 30.0f, 0xff000000, FW1_RESTORESTATE);

	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 34.0f, 30.0f, 0xff000000, FW1_RESTORESTATE);
	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 30.0f, 34.0f, 0xff000000, FW1_RESTORESTATE);

	DirectXRenderer::pFontWrapper->DrawString(DirectXRenderer::pContext, L"Loaded", fontsize, 32.0f, 32.0f, 0xffffffff, FW1_RESTORESTATE);*/

	ImGui_ImplDX11_NewFrame();

	if (show_app_about)
	{
		ImGuiIO& io = ImGui::GetIO();

		float screenWidth = io.DisplaySize.x * io.DisplayFramebufferScale.x;
		float screenHeight = io.DisplaySize.y * io.DisplayFramebufferScale.y;
		float windowScale = 1.0f;

		if (screenWidth < 1920.0f)
		{
			float diffrence = (1920.0f - screenWidth) / (1920.0f / 10.0f) * 0.1f;
			windowScale = 1.0f - diffrence;
		}
		
		if (g_Core)
		{
			if (g_Core->GetNetworkManager()->GetInterface()->IsActive())
			{
				ImGui::SetNextWindowPos(ImVec2(screenWidth - (600 * windowScale), screenHeight - (80 * windowScale) - 10));
				ImGui::SetNextWindowSize(ImVec2((600 * windowScale), (80 * windowScale)));
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::Begin("FiveMultiplayer_Debug", NULL, ImVec2(0, 0), 0.5f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
				{
					CVector3 pos = g_Core->GetLocalPlayer()->GetPos();
					CVector4 quat = g_Core->GetLocalPlayer()->GetQuat();
					float SizeH;

					//Position Debug
					std::string position = "Position: [X: " + std::to_string(pos.fX) + ", Y: " + std::to_string(pos.fY) + ", Z: " + std::to_string(pos.fZ) + "]";
					SizeH = ImGui::CalcTextSize(position.c_str()).x;

					ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - SizeH);
					ImGui::Text(position.c_str());
					ImGui::NewLine();

					//Quaternion Debug
					std::string quaternion = "Quaternion: [X: " + std::to_string(quat.fX) + ", Y: " + std::to_string(quat.fY) + ", Z: " + std::to_string(quat.fZ) + ", W: " + std::to_string(quat.fW) + "]";
					SizeH = ImGui::CalcTextSize(quaternion.c_str()).x;

					ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - SizeH);
					ImGui::Text(quaternion.c_str());
					ImGui::NewLine();

					// Pools Debug
					std::string pools = "Pools: Players(" + std::to_string(g_Core->GetStreamer()->GetPlayerCount()) + "/" + std::to_string(g_Players.size()) +
										"), Vehicles(" + std::to_string(g_Core->GetStreamer()->GetVehicleCount()) + "/" + std::to_string(g_Vehicles.size()) + 
										"), Objects(" + std::to_string(g_Core->GetStreamer()->GetObjectCount()) + "/" + std::to_string(g_Objects.size()) + "), Entities(" + std::to_string(g_Entities.size()) +  ")";
					SizeH = ImGui::CalcTextSize(pools.c_str()).x;

					ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - SizeH);
					ImGui::Text(pools.c_str());
					//ImGui::NewLine();
				}
				ImGui::End();
				ImGui::PopStyleVar(1);
			}
		}
	}

	//DirectXDraw::GetInstance()->BeginScene();
	//DirectXDraw::GetInstance()->DrawScene();
	//DirectXDraw::GetInstance()->EndScene();

	CefTexture::UpdateRenderTexture();
	CefTexture::DrawWebView();

	ImGui::Render();

	return DirectXRenderer::phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

void DirectXRenderer::Initialize()
{
	std::cout << "reach init" << std::endl;
	hWnd = FindWindowA(NULL, "Grand Theft Auto V");
	IDXGISwapChain* pSwapChain;

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0};
	D3D_FEATURE_LEVEL obtainedLevel;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevel, sizeof(featureLevel) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, &obtainedLevel, &pContext)))
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