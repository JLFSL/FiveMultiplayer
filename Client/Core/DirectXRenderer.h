#pragma once

class DirectXRenderer
{
public:
	static HWND hWnd;
	static bool FirstRender;

	static ID3D11Device *pDevice;
	static ID3D11DeviceContext *pContext;
	static IDXGISwapChain* pSwapChain;

	static IFW1Factory *pFW1Factory;
	static IFW1FontWrapper *pFontWrapper;

	static void Initialize();
	
	typedef HRESULT(WINAPI *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	static D3D11PresentHook phookD3D11Present;

	static ID3D11RenderTargetView* phookD3D11RenderTargetView;

	static DWORD_PTR* pSwapChainVtable;
	static DWORD_PTR* pDeviceContextVTable;
};

