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

void CleanupRenderTarget();
void CreateRenderTarget();

class DirectXRenderer
{
public:
	static std::mutex paintMutex;
	static std::list<std::unique_ptr<DrawData>> drawData;
	static ID3D11RenderTargetView* g_mainRenderTargetView;

	static HWND hWnd;
	static bool FirstRender;

	static ID3D11Device *pDevice;
	static ID3D11DeviceContext *pContext;
	static IDXGISwapChain* pSwapChain;

	static IFW1Factory *pFW1Factory;
	static IFW1FontWrapper *pFontWrapper;

	DirectXRenderer();
	~DirectXRenderer();

	static void Initialize();
	
	typedef HRESULT(WINAPI *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef void(WINAPI *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	typedef void(WINAPI *D3D11ClearRenderTargetViewHook) (ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

	void __stdcall DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	void __stdcall ClearRenderTargetView(ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

	const void* DetourFunc64(BYTE* const src, const BYTE* dest, const unsigned int jumplength);
	const unsigned int DisasmLengthCheck(const SIZE_T address, const unsigned int jumplength);

	static D3D11PresentHook phookD3D11Present;
	static D3D11DrawIndexedHook phookD3D11DrawIndexed;
	static D3D11ClearRenderTargetViewHook phookD3D11ClearRenderTargetView;
	static ID3D11RenderTargetView* phookD3D11RenderTargetView;

	static DWORD_PTR* pSwapChainVtable;
	static DWORD_PTR* pDeviceContextVTable;
};

