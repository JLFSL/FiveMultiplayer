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

struct Vertex2d {
	float x, y;
	float u, v;
};

class CefTexture
{
private:
	static const char PixelShaderSource[];
	static const char VertexShaderSource[];

	static ID3D11RenderTargetView* g_mainRenderTargetView;

	static ID3DBlob *PixelBlob;
	static ID3DBlob *VertexBlob;

	static ID3D11Buffer *WebViewGeometryBuffer;
	static ID3D11Texture2D *Texture;
	static ID3D11ShaderResourceView *TextureShaderResourceView;
	static ID3D11InputLayout *InputLayout;
	static ID3D11PixelShader *PixelShader;
	static ID3D11SamplerState *Sampler;
	static ID3D11BlendState *BlendState;
	static ID3D11RasterizerState * RasterizerState;
	static ID3D11DepthStencilState * DepthStencilState;
	static ID3D11VertexShader *VertexShader;

	static unsigned TextureWidth;
	static unsigned TextureHeight;

public:
	static bool CreateShaders();
	static bool CreateSampler();

	static bool CreateWebViewGeometryBuffer();

	static bool CreateTexture(unsigned Width, unsigned Height);
	static void UpdateRenderTexture();
	static void DestroyTexture();

	static void CreateRenderTarget();
	static void CleanupRenderTarget();

	static void DrawWebView();

	static bool SetupD3D();

	static std::mutex paintMutex;
	static std::list<std::unique_ptr<DrawData>> drawData;
};

