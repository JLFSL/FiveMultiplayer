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

HRESULT __stdcall Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	DirectXRenderer *curInstance = DirectXRenderer::GetInstance();

	if (DirectXRenderer::GetInstance()->FirstRender)
	{
		pSwapChain->GetDevice(__uuidof(curInstance->pDevice), (void**)&curInstance->pDevice);
		curInstance->pDevice->GetImmediateContext(&curInstance->pContext);

		FW1CreateFactory(FW1_VERSION, &curInstance->pFW1Factory);
		curInstance->pFW1Factory->CreateFontWrapper(curInstance->pDevice, L"Segoe UI", &curInstance->pFontWrapper);
		curInstance->pFW1Factory->Release();

		ImGui_ImplDX11_Init(curInstance->hWnd, curInstance->pDevice, curInstance->pContext);

		DirectXRenderer::GetInstance()->FirstRender = false;
	}

	curInstance->pFontWrapper->DrawString(curInstance->pContext, L"Loaded", 25.0f, 16.0f, 16.0f, 0xffffffff, FW1_RESTORESTATE);

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

	ImGui::Render();

	return DirectXRenderer::GetInstance()->phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

void DirectXRenderer::Initialize()
{
	hWnd = FindWindowA(NULL, "Grand Theft Auto V");
	IDXGISwapChain* pSwapChain;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;//((GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE; 
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, NULL, &pContext)))
	{
		MessageBoxA(hWnd, "Failed to load FiveMP with DirectX, make sure your game is using DirectX 11!", "FiveMP", MB_ICONERROR);
		return;
	}

	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pDeviceContextVTable = (DWORD_PTR*)pContext;
	pDeviceContextVTable = (DWORD_PTR*)pDeviceContextVTable[0];


	if (g_Config->GetSteam()) {
		phookD3D11Present = (D3D11PresentHook)DetourFunc64((BYTE*)pSwapChainVtable[8] + 0x5, (BYTE*)Present, 16);
	}
	else {
		phookD3D11Present = (D3D11PresentHook)DetourFunc64((BYTE*)pSwapChainVtable[8], (BYTE*)Present, 16);
	}

	//phookD3D11DrawIndexed = (D3D11DrawIndexedHook)DetourFunc64((BYTE*)pDeviceContextVTable[12], (BYTE*)hookD3D11DrawIndexed, 16);
	//phookD3D11ClearRenderTargetView = (D3D11ClearRenderTargetViewHook)DetourFunc64((BYTE*)pDeviceContextVTable[50], (BYTE*)hookD3D11ClearRenderTargetView, 16);

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();
}

const void* DirectXRenderer::DetourFunc64(BYTE* const src, const BYTE* dest, const unsigned int jumplength)
{
	// Allocate a memory page that is going to contain executable code. 
	MEMORY_BASIC_INFORMATION mbi;
	for (SIZE_T addr = (SIZE_T)src; addr > (SIZE_T)src - 0x80000000; addr = (SIZE_T)mbi.BaseAddress - 1)
	{
		if (!VirtualQuery((LPCVOID)addr, &mbi, sizeof(mbi)))
		{
			break;
		}

		if (mbi.State == MEM_FREE)
		{
			if (presenthook64 = (HookContext*)VirtualAlloc(mbi.BaseAddress, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE))
			{
				break;
			}
		}
	}

	// If allocating a memory page failed, the function failed. 
	if (!presenthook64)
	{
		return NULL;
	}

	// Select a pointer slot for the memory page to be freed on unload. 
	for (int i = 0; i < sizeof(detourBuffer) / sizeof(void*); ++i)
	{
		if (!detourBuffer[i])
		{
			detourBuffer[i] = presenthook64;
			break;
		}
	}

	// Save original code and apply detour. The detour code is: 
	// push rax 
	// movabs rax, 0xCCCCCCCCCCCCCCCC 
	// xchg rax, [rsp] 
	// ret 
	BYTE detour[] = { 0x50, 0x48, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0x87, 0x04, 0x24, 0xC3 };
	const unsigned int length = DisasmLengthCheck((SIZE_T)src, jumplength);
	memcpy(presenthook64->original_code, src, length);
	memcpy(&presenthook64->original_code[length], detour, sizeof(detour));
	*(SIZE_T*)&presenthook64->original_code[length + 3] = (SIZE_T)src + length;

	// Build a far jump to the destination function. 
	*(WORD*)&presenthook64->far_jmp = 0x25FF;
	*(DWORD*)(presenthook64->far_jmp + 2) = (DWORD)((SIZE_T)presenthook64 - (SIZE_T)src + FIELD_OFFSET(HookContext, dst_ptr) - 6);
	presenthook64->dst_ptr = (SIZE_T)dest;

	// Write the hook to the original function. 
	DWORD flOld = 0;
	VirtualProtect(src, 6, PAGE_EXECUTE_READWRITE, &flOld);
	memcpy(src, presenthook64->far_jmp, sizeof(presenthook64->far_jmp));
	VirtualProtect(src, 6, flOld, &flOld);

	// Return a pointer to the original code. 
	return presenthook64->original_code;
}

const unsigned int DirectXRenderer::DisasmLengthCheck(const SIZE_T address, const unsigned int jumplength)
{
	DISASM disasm;
	memset(&disasm, 0, sizeof(DISASM));

	disasm.EIP = (UIntPtr)address;
	disasm.Archi = 0x40;

	unsigned int processed = 0;
	while (processed < jumplength)
	{
		const int len = Disasm(&disasm);
		if (len == UNKNOWN_OPCODE)
		{
			++disasm.EIP;
		}
		else
		{
			processed += len;
			disasm.EIP += len;
		}
	}

	return processed;
}