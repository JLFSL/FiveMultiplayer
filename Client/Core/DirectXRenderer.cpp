#include "stdafx.h"

// class inits to prevent LNK2001
std::mutex DirectXRenderer::paintMutex;
std::list<std::unique_ptr<DrawData>> DirectXRenderer::drawData;
ID3D11RenderTargetView* DirectXRenderer::g_mainRenderTargetView = nullptr;

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

DirectXRenderer::DirectXRenderer()
{
	FirstRender = true;
	g_mainRenderTargetView = NULL;
}

DirectXRenderer::~DirectXRenderer()
{

}

bool show_app_about = true;

unsigned TextureWidth = 0, TextureHeight = 0;

#define SAFE_RELEASE(comObject) if (comObject) { comObject->Release(); comObject = NULL; }

ID3D11Buffer *WebViewGeometryBuffer = nullptr;
ID3D11Texture2D *CEFTexture = nullptr;
ID3D11ShaderResourceView *TextureShaderResourceView = nullptr;
ID3D11InputLayout *InputLayout = nullptr;
ID3D11PixelShader *PixelShader = nullptr;
ID3D11SamplerState *Sampler = nullptr;
ID3D11BlendState *BlendState = nullptr;
ID3D11RasterizerState * RasterizerState = nullptr;
ID3D11DepthStencilState * DepthStencilState = nullptr;
ID3D11VertexShader *VertexShader = nullptr;

ID3DBlob *PixelBlob = nullptr;
ID3DBlob *VertexBlob = nullptr;

struct Vertex2d {
	float x, y;
	float u, v;
};

const char PixelShaderSource[] = {
	"Texture2D diffuse;\n\
sampler sampler0;\n\
\n\
struct INPUT \n\
{ \n\
	float2 uv : TEXCOORD; \n\
};\n\
\n\
float4 main(INPUT input) : SV_TARGET\n\
{\n\
	float4 output = diffuse.Sample(sampler0, input.uv);\n\
	return output;\n\
}"
};

const char VertexShaderSource[] = {
	"struct INPUT \
{ \
	float2 pos : POSITION; \
	float2 uv : TEXCOORD; \
};\
\
struct OUTPUT \
{ \
	float2 uv : TEXCOORD; \
	float4 pos : SV_POSITION; \
};\
\
OUTPUT main(INPUT input)\
{\
	OUTPUT output;\
	output.uv = input.uv;\
	output.pos = float4(input.pos.x, input.pos.y, 0.0f, 1.0f);\
	return output;\
}"
};

bool CreateShaders()
{
	ID3DBlob *ErrorMsg = nullptr;
	if (FAILED(D3DCompile(PixelShaderSource, strlen(PixelShaderSource), NULL, NULL, NULL, "main", "ps_4_0", 0, 0, &PixelBlob, &ErrorMsg))) {
		const char *const ERROR_BASE = "Failed to compile pixel shader.";
		char *const error = new char[strlen(ERROR_BASE) + ErrorMsg->GetBufferSize() + strlen(PixelShaderSource) + 1 + 2 /*new lines */];
		sprintf(error, "%s\n%s\n%s", ERROR_BASE, (const char *)ErrorMsg->GetBufferPointer(), PixelShaderSource);
		MessageBox(NULL, error, NULL, NULL);
		delete[]error;
		return false;
	}

	if (FAILED(DirectXRenderer::pDevice->CreatePixelShader(PixelBlob->GetBufferPointer(), PixelBlob->GetBufferSize(), NULL, &PixelShader))) {
		MessageBox(NULL, "Failed to create pixel shader.", NULL, NULL);
		return false;
	}

	if (FAILED(D3DCompile(VertexShaderSource, strlen(VertexShaderSource), NULL, NULL, NULL, "main", "vs_4_0", 0, 0, &VertexBlob, &ErrorMsg))) {
		const char *const ERROR_BASE = "Failed to compile vertex shader.";
		char *const error = new char[strlen(ERROR_BASE) + ErrorMsg->GetBufferSize() + strlen(VertexShaderSource) + 1 + 2 /*new lines */];
		sprintf(error, "%s\n%s\n%s", ERROR_BASE, (const char *)ErrorMsg->GetBufferPointer(), VertexShaderSource);
		MessageBox(NULL, error, NULL, NULL);
		delete[]error;
		return false;
	}

	if (FAILED(DirectXRenderer::pDevice->CreateVertexShader(VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), NULL, &VertexShader))) {
		MessageBox(NULL, "Failed to create vertex shader.", NULL, NULL);
		return false;
	}

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0.f;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.MinLOD = 0.f;
	desc.MaxLOD = 0.f;
	DirectXRenderer::pDevice->CreateSamplerState(&desc, &Sampler);
	return true;
}

bool CreateSampler()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0.f;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.MinLOD = 0.f;
	desc.MaxLOD = 0.f;


	if (FAILED(DirectXRenderer::pDevice->CreateSamplerState(&desc, &Sampler))) {
		MessageBox(NULL, "Failed to create sampler state.", NULL, NULL);
		return false;
	}
	return true;
}

bool CreateTexture(unsigned Width, unsigned Height)
{
	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));

	desc.Width = Width;
	desc.Height = Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = DirectXRenderer::pDevice->CreateTexture2D(&desc, NULL, &CEFTexture);
	if (FAILED(hr)) {
		char error[256] = { 0 };
		sprintf(error, "Failed to create texture (%X)", hr);
		MessageBox(NULL, error, NULL, NULL);
		return false;
	}

	if (FAILED(DirectXRenderer::pDevice->CreateShaderResourceView(CEFTexture, NULL, &TextureShaderResourceView))) {
		MessageBox(NULL, "Failed to create shader resource view for texture.", NULL, NULL);
		return false;
	}

	TextureWidth = Width;
	TextureHeight = Height;
	return true;
}

void DestroyTexture()
{
	SAFE_RELEASE(CEFTexture);
}

void DrawWebView()
{
	if (!WebViewGeometryBuffer) {
		return;
	}

	UINT Stride = sizeof(Vertex2d);
	UINT Offset = 0;

	DirectXRenderer::pContext->IASetInputLayout(InputLayout);
	DirectXRenderer::pContext->IASetVertexBuffers(0, 1, &WebViewGeometryBuffer, &Stride, &Offset);
	DirectXRenderer::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DirectXRenderer::pContext->VSSetShader(VertexShader, NULL, 0);

	DirectXRenderer::pContext->PSSetShaderResources(0, 1, &TextureShaderResourceView);
	DirectXRenderer::pContext->PSSetSamplers(0, 1, &Sampler);
	DirectXRenderer::pContext->PSSetShader(PixelShader, NULL, 0);

	DirectXRenderer::pContext->Draw(6, 0);
}

void UpdateRenderTexture()
{
	std::unique_ptr<DrawData> data;
	{
		std::lock_guard<std::mutex> lock(DirectXRenderer::paintMutex);
		if (DirectXRenderer::drawData.empty()) {
			return;
		}

		data = std::move(DirectXRenderer::drawData.front());
		DirectXRenderer::drawData.pop_front();
	}

	// In case texture size changed recreate it (also handles creation)
	if (TextureWidth != data->width || TextureHeight != data->height) {
		DestroyTexture();
		CreateTexture(data->width, data->height);
	}

	// Not texture no fun :-(
	if (!CEFTexture) {
		return;
	}


	D3D11_MAPPED_SUBRESOURCE subRes;
	if (FAILED(DirectXRenderer::pContext->Map(CEFTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes))) {
		return;
	}

	unsigned *pixels = (unsigned *)subRes.pData;
	const unsigned *cefPixels = (const unsigned *)data->pixels;
	memcpy(pixels, cefPixels, TextureWidth * TextureHeight * 4);


	/*for (size_t i = 0; i < data->dirtyRects.size(); ++i) {
	const CefRect &rct = data->dirtyRects[i];

	for (int x = rct.x; x < rct.x + rct.width; ++x) {
	for (int y = rct.y; y < rct.y + rct.height; ++y) {
	pixels[y * data->width + x] = cefPixels[y * data->width + x];
	}
	}
	}*/

	DirectXRenderer::pContext->Unmap(CEFTexture, 0);
}

bool CreateWebViewGeometryBuffer()
{
	// 1/4 of the screen, top right to bottom left
	/*Vertex2d rect[6] = {
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },

		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 0.0f }
	};*/
	// fullscreen
	Vertex2d rect[6] = {
		{ -1.0f, 1.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, 0.0f, 1.0f },

		{ -1.0f, -1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 0.0f },
		{ 1.0f, -1.0f, 1.0f, 1.0f }
	};

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));

	bufferDesc.ByteWidth = sizeof(Vertex2d) * 6;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data;
	memset(&data, 0, sizeof(data));
	data.pSysMem = rect;

	if (FAILED(DirectXRenderer::pDevice->CreateBuffer(&bufferDesc, &data, &WebViewGeometryBuffer))) {
		MessageBox(NULL, "Failed to create buffer", NULL, NULL);
		return false;
	}

	if (!VertexBlob) return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex2d, x), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex2d, u), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT hr = DirectXRenderer::pDevice->CreateInputLayout(layout, 2, VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), &InputLayout);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create input layout", NULL, NULL);
		return false;
	}

	VertexBlob->Release();
	VertexBlob = nullptr;

	PixelBlob->Release();
	PixelBlob = nullptr;
	return true;
}

bool SetupD3D()
{
	if (!CreateShaders()) {
		return false;
	}
	if (!CreateSampler()) {
		return false;
	}

	if (!CreateWebViewGeometryBuffer()) {
		return false;
	}

	const D3D11_VIEWPORT viewport = { 0.0f, 0.0f, 1600.0f, 900.0f, 0.0f, 1.0f };
	DirectXRenderer::pContext->RSSetViewports(1, &viewport);

	{
		D3D11_BLEND_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.AlphaToCoverageEnable = false;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		if (FAILED(DirectXRenderer::pDevice->CreateBlendState(&desc, &BlendState))) {
			return false;
		}
	}

	const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
	DirectXRenderer::pContext->OMSetBlendState(BlendState, blend_factor, 0xffffffff);
	{
		D3D11_RASTERIZER_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_NONE;
		desc.ScissorEnable = false;
		desc.DepthClipEnable = false;
		if (FAILED(DirectXRenderer::pDevice->CreateRasterizerState(&desc, &RasterizerState))) {
			return false;
		}
	}
	DirectXRenderer::pContext->RSSetState(RasterizerState);

	{
		D3D11_DEPTH_STENCIL_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.DepthEnable = false;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		desc.StencilEnable = false;
		desc.FrontFace.StencilFailOp = desc.FrontFace.StencilDepthFailOp = desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		desc.BackFace = desc.FrontFace;
		if (FAILED(DirectXRenderer::pDevice->CreateDepthStencilState(&desc, &DepthStencilState))) {
			return false;
		}
	}
	DirectXRenderer::pContext->OMSetDepthStencilState(DepthStencilState, 0);
	return true;
}

void CreateRenderTarget()
{
	DXGI_SWAP_CHAIN_DESC sd;
	DirectXRenderer::pSwapChain->GetDesc(&sd);

	// Create the render target
	ID3D11Texture2D* pBackBuffer;
	D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
	ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
	render_target_view_desc.Format = sd.BufferDesc.Format;
	render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	DirectXRenderer::pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	DirectXRenderer::pDevice->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &DirectXRenderer::g_mainRenderTargetView);
	DirectXRenderer::pContext->OMSetRenderTargets(1, &DirectXRenderer::g_mainRenderTargetView, NULL);
	pBackBuffer->Release();
}

void CleanupRenderTarget()
{
	if (DirectXRenderer::g_mainRenderTargetView) { DirectXRenderer::g_mainRenderTargetView->Release(); DirectXRenderer::g_mainRenderTargetView = NULL; }
}

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
		
		//if (!SetupD3D())
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
				ImGui::SetNextWindowPos(ImVec2(screenWidth - (700 * windowScale), screenHeight - (80 * windowScale) - 10));
				ImGui::SetNextWindowSize(ImVec2((700 * windowScale), (80 * windowScale)));
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

	UpdateRenderTexture();
	DrawWebView();

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