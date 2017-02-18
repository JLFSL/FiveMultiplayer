#pragma once

struct DrawData
{
	unsigned *pixels;
	unsigned width;
	unsigned height;
	CefRenderHandler::RectList dirtyRects;

	DrawData(unsigned theWidth, unsigned theHeight, const unsigned *thePixels, const CefRenderHandler::RectList& theDirtyRects)
	{
		pixels = new unsigned[theWidth * theHeight];
		width = theWidth;
		height = theHeight;
		memcpy(pixels, thePixels, 4 * width*height);
		dirtyRects = theDirtyRects;
	}

	~DrawData()
	{
		delete[]pixels;
		pixels = nullptr;
	}
};

class DirectXRenderer
{
public:
	std::mutex paintMutex;
	std::list<std::unique_ptr<DrawData>> drawData;

	HWND hWnd; 
	bool FirstRender;

	ID3D11Device *pDevice;
	ID3D11DeviceContext *pContext;

	IFW1Factory *pFW1Factory;
	IFW1FontWrapper *pFontWrapper;

	DirectXRenderer();
	~DirectXRenderer();

	void Initialize();
	
	typedef HRESULT(WINAPI *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef void(WINAPI *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	typedef void(WINAPI *D3D11ClearRenderTargetViewHook) (ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

	void __stdcall DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	void __stdcall ClearRenderTargetView(ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

	const void* DetourFunc64(BYTE* const src, const BYTE* dest, const unsigned int jumplength);
	const unsigned int DisasmLengthCheck(const SIZE_T address, const unsigned int jumplength);

	static DirectXRenderer* GetInstance() { return Instance; }

	D3D11PresentHook phookD3D11Present;
	D3D11DrawIndexedHook phookD3D11DrawIndexed;
	D3D11ClearRenderTargetViewHook phookD3D11ClearRenderTargetView;
	ID3D11RenderTargetView* phookD3D11RenderTargetView;

private:
	DWORD_PTR* pSwapChainVtable;
	DWORD_PTR* pDeviceContextVTable;
	
	static DirectXRenderer* Instance;
};

