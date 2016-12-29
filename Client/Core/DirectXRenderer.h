#pragma once
class DirectXRenderer
{
public:
	HWND hWnd; 
	bool FirstRender;

	ID3D11Device *pDevice;
	ID3D11DeviceContext *pContext;

	IFW1Factory *pFW1Factory;
	IFW1FontWrapper *pFontWrapper;

	DirectXRenderer();
	~DirectXRenderer();

	void Initialize();
	
	typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef void(__stdcall *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	typedef void(__stdcall *D3D11ClearRenderTargetViewHook) (ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

	void __stdcall DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	void __stdcall ClearRenderTargetView(ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

	const void* DetourFunc64(BYTE* const src, const BYTE* dest, const unsigned int jumplength);
	const unsigned int DisasmLengthCheck(const SIZE_T address, const unsigned int jumplength);

	static DirectXRenderer* GetInstance() { return Instance; }

	D3D11PresentHook phookD3D11Present;
	D3D11DrawIndexedHook phookD3D11DrawIndexed;
	D3D11ClearRenderTargetViewHook phookD3D11ClearRenderTargetView;

	void* GetBuffer() { return detourBuffer; }

private:
	DWORD_PTR* pSwapChainVtable;
	DWORD_PTR* pDeviceContextVTable;
	
	static DirectXRenderer* Instance;

	struct HookContext
	{
		BYTE original_code[64];
		SIZE_T dst_ptr;
		BYTE far_jmp[6];
	};
	HookContext* presenthook64;
	void* detourBuffer[3];
};

