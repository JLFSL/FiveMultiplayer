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

ID3D11RenderTargetView* DirectXRenderer::phookD3D11RenderTargetView;

DWORD_PTR* DirectXRenderer::pSwapChainVtable = nullptr;
DWORD_PTR* DirectXRenderer::pDeviceContextVTable = nullptr;

bool show_app_about = true;

char InputBuf[256];
float DirectXRenderer::windowScale = 1.0f;
float DirectXRenderer::textScale = 0.5f;

HRESULT WINAPI Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (DirectXRenderer::FirstRender)
	{
		pSwapChain->GetDevice(__uuidof(DirectXRenderer::pDevice), (void**)&DirectXRenderer::pDevice);
		DirectXRenderer::pDevice->GetImmediateContext(&DirectXRenderer::pContext);

		FW1CreateFactory(FW1_VERSION, &DirectXRenderer::pFW1Factory);
		DirectXRenderer::pFW1Factory->CreateFontWrapper(DirectXRenderer::pDevice, L"Segoe UI", &DirectXRenderer::pFontWrapper);
		DirectXRenderer::pFW1Factory->Release();

		//DirectXDraw::GetInstance()->Initialize();

		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChain->GetDesc(&sd);

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

	CefTexture::UpdateRenderTexture();
	CefTexture::DrawWebView();

	ImGuiIO& io = ImGui::GetIO();

	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(DirectXRenderer::hWnd, &cursor);
	io.MousePos.x = cursor.x;
	io.MousePos.y = cursor.y;

	ImGui_ImplDX11_NewFrame();

	//io.MouseDrawCursor = true;

	if (show_app_about)
	{
		float screenWidth = io.DisplaySize.x * io.DisplayFramebufferScale.x;
		float screenHeight = io.DisplaySize.y * io.DisplayFramebufferScale.y;
		DirectXRenderer::windowScale = 1.0f;
		DirectXRenderer::textScale = 1.0f;

		if (screenWidth < 1920.0f)
		{
			float diffrence = (1920.0f - screenWidth) / (1920.0f / 10.0f) * 0.1f;
			DirectXRenderer::windowScale = 1.0f - diffrence;
			DirectXRenderer::textScale = 1.0f - (diffrence - (diffrence / 2));
			if (DirectXRenderer::textScale < 0.75f)
				DirectXRenderer::textScale = 0.75f;
		}
		
		if (CNetworkManager::g_ConnectionState == CONSTATE_COND)
		{
			ImGui::SetNextWindowPos(ImVec2(screenWidth - (700 * DirectXRenderer::windowScale), screenHeight - (80 * DirectXRenderer::windowScale) - 10));
			ImGui::SetNextWindowSize(ImVec2((700 * DirectXRenderer::windowScale), (80 * DirectXRenderer::windowScale)));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::Begin("FiveMultiplayer_Debug", NULL, ImVec2(0, 0), 0.5f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
			{
				ImGui::SetWindowFontScale(DirectXRenderer::textScale);
				CVector3 pposition = CLocalPlayer::GetPosition();
				CVector3 protation = CLocalPlayer::GetRotation();
				float SizeH;

				//Position Debug
				std::string position = "Position: [X: " + std::to_string(pposition.fX) + ", Y: " + std::to_string(pposition.fY) + ", Z: " + std::to_string(pposition.fZ) + "]";
				SizeH = ImGui::CalcTextSize(position.c_str()).x;

				ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - SizeH);
				ImGui::Text(position.c_str());
				ImGui::NewLine();

				//Rotation Debug
				std::string rotation = "Rotation: [X: " + std::to_string(protation.fX) + ", Y: " + std::to_string(protation.fY) + ", Z: " + std::to_string(protation.fZ) + "]";
				SizeH = ImGui::CalcTextSize(rotation.c_str()).x;

				ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - SizeH);
				ImGui::Text(rotation.c_str());
				ImGui::NewLine();

				// Pools Debug
				std::string pools = "Pools: Players(" + std::to_string(CStreamer::GetPlayerCount()) + "/" + std::to_string(g_Players.size()) +
									"), Vehicles(" + std::to_string(CStreamer::GetVehicleCount()) + "/" + std::to_string(g_Vehicles.size()) + 
									"), Objects(" + std::to_string(CStreamer::GetObjectCount()) + "/" + std::to_string(g_Objects.size()) + 
									"), NPCs(" + std::to_string(CStreamer::GetNpcCount()) + "/" + std::to_string(g_Npcs.size()) +
									"), Entities(" + std::to_string(g_Entities.size()) +  ")";
				SizeH = ImGui::CalcTextSize(pools.c_str()).x;

				ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - SizeH);
				ImGui::Text(pools.c_str());
				//ImGui::NewLine();
			}
			ImGui::End();
			ImGui::PopStyleVar(1);
		}

		if (CNetworkManager::g_ConnectionState == CONSTATE_CONN)
		{
			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			ImGui::SetNextWindowSize(ImVec2((500 * DirectXRenderer::windowScale), (60 * DirectXRenderer::windowScale)));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::Begin("FiveMultiplayer_Connecting", NULL, ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
			{
				ImGui::SetWindowFontScale(2.0f);
				ImGui::Text("Connecting....");
			}
			ImGui::End();
			ImGui::PopStyleVar(1);
		}

		// Temporary Chat
		if (CNetworkManager::g_ConnectionState == CONSTATE_COND && CConfig::GetUILevel() < 2)
		{
			ImGui::SetNextWindowPos(ImVec2(3, 3));
			ImGui::SetNextWindowSize(ImVec2((800 * DirectXRenderer::windowScale), (400 * DirectXRenderer::windowScale)));
			ImGui::Begin(" ", NULL, ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize);
			{
				ImGui::SetWindowFontScale(DirectXRenderer::textScale * 1.2f);
				ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_NoScrollbar);
				{
					ImGui::SetWindowFontScale(DirectXRenderer::textScale * 1.2f);
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1)); // Tighten spacing
					ImVec4 cBg = ImVec4(0.20f, 0.20f, 0.20f, 0.0f);
					ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, cBg);
					ImGui::PushTextWrapPos(ImGui::GetWindowWidth() - 3.0f);

					if (!CChat::chatData.empty())
					{
						int maxLines = CChat::chatData.size();
						if (maxLines > CChat::MaxHistory)
							maxLines = CChat::MaxHistory;

						for (int i = 0; i < maxLines; i++)
						{
							if (CChat::chatData[i].used)
							{
								for (int h = 0; h < CChat::chatData[i].message.size(); h++)
								{
									if (!CChat::chatData[i].message.empty())
									{
										if (h != 0)
											ImGui::SameLine();

										ImVec4 col = ImVec4(CChat::chatData[i].message[h].red, CChat::chatData[i].message[h].green, CChat::chatData[i].message[h].blue, 1.0f);
										ImGui::PushStyleColor(ImGuiCol_Text, col);

										if (CChat::chatData[i].message[h].newline)
											ImGui::NewLine();

										if (CChat::chatData[i].message[h].text.c_str())
										{
											ImGui::TextUnformatted(CString::utf16ToUtf8(CChat::chatData[i].message[h].text).c_str());
										}

										ImGui::PopStyleColor();
									}
								}
							}
						}
					}

					if (CChat::ScrollToBottom)
						ImGui::SetScrollHere();

					CChat::ScrollToBottom = false;
					ImGui::PopStyleVar();
					ImGui::PopStyleColor();
				}
				ImGui::EndChild();

				// Command-line
				if (CChat::InputOpen)
				{
					//LocalPlayer.controllable = false;
					io.MouseDrawCursor = true;
					ImGui::PushItemWidth(-1);
					if (ImGui::InputText("", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue))
					{
						char* input_end = InputBuf + strlen(InputBuf);
						while (input_end > InputBuf && input_end[-1] == ' ') input_end--; *input_end = 0;
						if (InputBuf[0])
						{
							if (InputBuf[0] == L'/' && CChat::CommandProcessor(CString::utf8ToUtf16(InputBuf))) {}
							else 
							{
								std::wstring message = CString::utf8ToUtf16(InputBuf);
								for (int m = 0; m < message.size() * sizeof(wchar_t); m++)
								{
									if (message.data()[m] == '{') 
									{
										if (m + 7 < message.size() * sizeof(wchar_t))
										{
											if (message.data()[m + 7] == '}') 
											{
												message.erase(m, 8);
											}
										}
									}
								}

								BitStream bitstream;
								RakNet::RakWString msg(message.c_str());

								bitstream.Write((unsigned char)ID_CHAT_MESSAGE);
								bitstream.Write(msg);

								CNetworkManager::GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false);
							}
						}

						strcpy(InputBuf, "");
						CChat::InputOpen = false;
						//LocalPlayer.controllable = true;
						io.MouseDrawCursor = false;
					}
					ImGui::PopItemWidth();

					ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
				}
			}
			ImGui::End();
		}
	}

	ImGui::Render();

	//DirectXDraw::GetInstance()->BeginScene();
	//DirectXDraw::GetInstance()->DrawScene();
	//DirectXDraw::GetInstance()->EndScene();

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

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	
	//swapChainDesc.BufferDesc.Width = 0;
	//swapChainDesc.BufferDesc.Height = 0;
	//swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	//swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = TRUE;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	// This flag gives you some quite wonderful debug text. Not wonderful for performance, though!
	//createFlags |= D3D11_CREATE_DEVICE_DEBUG; ///WERE IS THIS?
#endif

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