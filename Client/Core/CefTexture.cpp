#include "stdafx.h"

ID3D11RenderTargetView* CefTexture::g_mainRenderTargetView = nullptr;

ID3DBlob *CefTexture::PixelBlob = nullptr;
ID3DBlob *CefTexture::VertexBlob = nullptr;

ID3D11Buffer *CefTexture::WebViewGeometryBuffer = nullptr;
ID3D11Texture2D *CefTexture::Texture = nullptr;
ID3D11ShaderResourceView *CefTexture::TextureShaderResourceView = nullptr;
ID3D11InputLayout *CefTexture::InputLayout = nullptr;
ID3D11PixelShader *CefTexture::PixelShader = nullptr;
ID3D11SamplerState *CefTexture::Sampler = nullptr;
ID3D11BlendState *CefTexture::BlendState = nullptr;
ID3D11RasterizerState *CefTexture::RasterizerState = nullptr;
ID3D11DepthStencilState *CefTexture::DepthStencilState = nullptr;
ID3D11VertexShader *CefTexture::VertexShader = nullptr;

unsigned CefTexture::TextureWidth = 0;
unsigned CefTexture::TextureHeight = 0;

std::mutex CefTexture::paintMutex;
std::list<std::unique_ptr<DrawData>> CefTexture::drawData;

const char CefTexture::PixelShaderSource[] = {
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

const char CefTexture::VertexShaderSource[] = {
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

bool CefTexture::CreateShaders()
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

bool CefTexture::CreateSampler()
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

bool CefTexture::CreateWebViewGeometryBuffer()
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

bool CefTexture::CreateTexture(unsigned Width, unsigned Height)
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

	HRESULT hr = DirectXRenderer::pDevice->CreateTexture2D(&desc, NULL, &Texture);
	if (FAILED(hr)) {
		char error[256] = { 0 };
		sprintf(error, "Failed to create texture (%X)", hr);
		MessageBox(NULL, error, NULL, NULL);
		return false;
	}

	if (FAILED(DirectXRenderer::pDevice->CreateShaderResourceView(Texture, NULL, &TextureShaderResourceView))) {
		MessageBox(NULL, "Failed to create shader resource view for texture.", NULL, NULL);
		return false;
	}

	TextureWidth = Width;
	TextureHeight = Height;
	return true;
}

void CefTexture::UpdateRenderTexture()
{
	std::unique_ptr<DrawData> data;
	{
		std::lock_guard<std::mutex> lock(paintMutex);
		if (drawData.empty()) {
			return;
		}

		data = std::move(drawData.front());
		drawData.pop_front();
	}

	// In case texture size changed recreate it (also handles creation)
	if (TextureWidth != data->width || TextureHeight != data->height) {
		DestroyTexture();
		CreateTexture(data->width, data->height);
	}

	// Not texture no fun :-(
	if (!Texture) {
		return;
	}


	D3D11_MAPPED_SUBRESOURCE subRes;
	if (FAILED(DirectXRenderer::pContext->Map(Texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes))) {
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

	DirectXRenderer::pContext->Unmap(Texture, 0);
}

void CefTexture::DestroyTexture()
{
	SAFE_RELEASE(Texture);
}

void CefTexture::CreateRenderTarget()
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
	DirectXRenderer::pDevice->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &g_mainRenderTargetView);
	DirectXRenderer::pContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	pBackBuffer->Release();
}

void CefTexture::CleanupRenderTarget()
{
	if (g_mainRenderTargetView) 
	{
		g_mainRenderTargetView->Release();
		g_mainRenderTargetView = NULL;
	}
}

void CefTexture::DrawWebView()
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

bool CefTexture::SetupD3D()
{
	if (!CreateShaders())
	{
		std::cout << "failed: CreateShaders" << std::endl;
		return false;
	}

	if (!CreateSampler()) 
	{
		std::cout << "failed: CreateSampler" << std::endl;
		return false;
	}

	if (!CreateWebViewGeometryBuffer()) 
	{
		std::cout << "failed: CreateWebViewGeometryBuffer" << std::endl;
		return false;
	}

	const D3D11_VIEWPORT viewport = { 
		0.0f, 0.0f, 
		1280.0f, 720.0f, 
		0.0f, 1.0f 
	};

	DirectXRenderer::pContext->RSSetViewports(1, &viewport);
	{
		D3D11_BLEND_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; 
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		if (FAILED(DirectXRenderer::pDevice->CreateBlendState(&desc, &BlendState)))
		{
			std::cout << "failed: CreateBlendState" << std::endl;
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
		if (FAILED(DirectXRenderer::pDevice->CreateRasterizerState(&desc, &RasterizerState)))
		{
			std::cout << "failed: CreateRasterizerState" << std::endl;
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
		if (FAILED(DirectXRenderer::pDevice->CreateDepthStencilState(&desc, &DepthStencilState)))
		{
			std::cout << "failed: CreateDepthStencilState" << std::endl;
			return false;
		}
	}

	DirectXRenderer::pContext->OMSetDepthStencilState(DepthStencilState, 0);
	return true;
}
