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
bool DirectXRenderer::showServerList = false;
bool DirectXRenderer::showOptions = false;

int loadingProg = 0;

char InputBuf[256];
float DirectXRenderer::windowScale = 1.0f;
float DirectXRenderer::textScale = 0.5f;

std::string DirectXRenderer::ConnectionProg = "Establishing Connection";

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

		ImGuiStyle& style = ImGui::GetStyle();
		bool bStyleDark_ = true;
		float alpha_ = 1.0;

		// light style from Pacôme Danhiez (user itamago) https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
		style.Alpha = 1.0f;
		style.FrameRounding = 1.0f;
		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(.0f, .0f, .0f, .0f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.953f, 0.255f, 0.29f, 0.40f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.953f, 0.255f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.953f, 0.255f, 0.29f, 0.35f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

		
		ImGuiIO& ioinit = ImGui::GetIO();
		//ioinit.Fonts->AddFontDefault();

		//Default (English & Cyrillic)
		ImFontConfig font_config;
		font_config.MergeMode = true;
		font_config.OversampleH = font_config.OversampleV = 1;
		font_config.PixelSnapH = true;
		ioinit.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Roboto-Regular.ttf", 40.0f);

		//Cyrillic
		ioinit.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Roboto-Regular.ttf", 40.0f, &font_config, ioinit.Fonts->GetGlyphRangesCyrillic());

		//Chinese (FallBack No Roboto Support for this language)
		ioinit.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\simhei.ttf", 40.0f, &font_config, ioinit.Fonts->GetGlyphRangesChinese());

		// Korean (FallBack No Roboto Support for this language)
		ioinit.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\batang.ttc", 40.0f, &font_config, ioinit.Fonts->GetGlyphRangesKorean());

		// Japanese (FallBack No Roboto Support for this language)
		ioinit.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryob.ttc", 40.0f, &font_config, ioinit.Fonts->GetGlyphRangesJapanese());

		// Thai (FallBack No Roboto Support for this language)
		ioinit.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\browalia.ttc", 40.0f, &font_config, ioinit.Fonts->GetGlyphRangesThai());

		//WindowManager->HugeFont = ioinit.Fonts->AddFontFromFileTTF("Roboto-Regular.ttf", 80.0f);

		ioinit.Fonts->Build();
		

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
		
		if (CNetworkManager::g_ConnectionState == CONSTATE_DISC && Hooking::GetGameState() == GameStatePlaying) {
			io.MouseDrawCursor = true;

			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(screenWidth/5, screenHeight));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::Begin("FiveMultiplayer_Main", NULL, ImVec2(0, 0), 0.7f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
			{
				ImGui::SetWindowFontScale(DirectXRenderer::textScale);
				//ImGui::PushFont(HugeFont);
				float SizeH1 = ImGui::CalcTextSize("Five Multiplayer").x;
				float SizeH3 = ImGui::CalcTextSize("Five ").x;
				float SizeH2 = ImGui::CalcTextSize("Multiplayer").x;

				ImGui::NewLine(); ImGui::NewLine();
				ImGui::SameLine((ImGui::GetWindowContentRegionMax().x / 2) - (SizeH1 / 2));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
				ImGui::Text("Five ");
				ImGui::PopStyleColor();
				ImGui::SameLine((ImGui::GetWindowContentRegionMax().x / 2) - (SizeH1 / 2) + SizeH3);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
				ImGui::Text("Multiplayer");
				ImGui::PopStyleColor();

				ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine();
				ImGui::SameLine((ImGui::GetWindowContentRegionMax().x / 2) - 150);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 10));

				if(DirectXRenderer::showServerList)
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.953f, 0.255f, 0.29f, 1.00f));
				else
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.0f, .0f, .0f, .0f));

				if (ImGui::Button("Server List", ImVec2(300, 0))) {
					DirectXRenderer::showServerList = !DirectXRenderer::showServerList;
					DirectXRenderer::showOptions = false;
				}

				ImGui::NewLine();
				ImGui::SameLine((ImGui::GetWindowContentRegionMax().x / 2) - 150);

				if (DirectXRenderer::showOptions)
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.953f, 0.255f, 0.29f, 1.00f));
				else
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.0f, .0f, .0f, .0f));

				if (ImGui::Button("Options", ImVec2(300, 0))) {
					DirectXRenderer::showServerList = false;
					DirectXRenderer::showOptions = !DirectXRenderer::showOptions;
				}

				ImGui::NewLine();
				ImGui::SameLine((ImGui::GetWindowContentRegionMax().x / 2) - 150);

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.0f, .0f, .0f, .0f));

				if (ImGui::Button("Exit", ImVec2(300, 0))) {
					CNetworkManager::Stop();
					exit(EXIT_SUCCESS);
				}

				ImGui::PopStyleColor(4);
				ImGui::PopStyleVar(1);
				

			}
			ImGui::End();
			ImGui::PopStyleVar(1);

			if (!DirectXRenderer::showServerList && !DirectXRenderer::showOptions) {
				ImGui::SetNextWindowPos(ImVec2((screenWidth / 5) + 10, 10));
				ImGui::SetNextWindowSize(ImVec2((screenWidth / 5) * 4 - 20, 80));
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::Begin("FiveMultiplayer_Info", NULL, ImVec2(0, 0), 0.7f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
				{
					ImGui::SetWindowFontScale(DirectXRenderer::textScale/2);
					ImGui::Text("Welcome to Five Multiplayer");
					ImGui::Text("This Pre-Release version of 0.2a and not the full release of 0.2a");
					ImGui::Text("- FiveMP Team");
				}
				ImGui::End();
				ImGui::PopStyleVar(1);
			}

			if (DirectXRenderer::showServerList) {
				ImGui::SetNextWindowPos(ImVec2((screenWidth / 5) + 10, 10));
				ImGui::SetNextWindowSize(ImVec2((screenWidth / 5) * 4 - 20, screenHeight - 20));
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::Begin("FiveMultiplayer_Server", NULL, ImVec2(0, 0), 0.7f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
				{
					ImGui::SetWindowFontScale(DirectXRenderer::textScale);

					float SizeH1 = ImGui::CalcTextSize("Server List").x;
					ImGui::SameLine((ImGui::GetWindowContentRegionMax().x / 2) - (SizeH1 / 2));
					ImGui::Text("Server List");


				}
				ImGui::End();
				ImGui::PopStyleVar(1);
			}
		}

		if (CNetworkManager::g_ConnectionState == CONSTATE_COND)
		{
			ImGui::SetNextWindowPos(ImVec2(screenWidth - (700 * DirectXRenderer::windowScale), screenHeight - (80 * DirectXRenderer::windowScale) - 10));
			ImGui::SetNextWindowSize(ImVec2((700 * DirectXRenderer::windowScale), (80 * DirectXRenderer::windowScale)));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::Begin("FiveMultiplayer_Debug", NULL, ImVec2(0, 0), 0.5f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
			{
				ImGui::SetWindowFontScale(DirectXRenderer::textScale/3);
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
			ImGui::SetNextWindowPos(ImVec2((screenWidth / 2) - ((500 * DirectXRenderer::windowScale) / 2), 20));
			ImGui::SetNextWindowSize(ImVec2((500 * DirectXRenderer::windowScale), (100 * DirectXRenderer::windowScale)));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::Begin("FiveMultiplayer_Connecting", NULL, ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
			{
				ImGui::SetWindowFontScale(DirectXRenderer::textScale);
				if(loadingProg >= 0 && loadingProg < 10)
					ImGui::Text("Connecting..");
				else if (loadingProg >= 10 && loadingProg < 20)
					ImGui::Text("Connecting...");

				if (loadingProg >= 20 && loadingProg < 30)
					ImGui::Text("Connecting....");

				if (loadingProg >= 30 && loadingProg < 40)
				{
					ImGui::Text("Connecting.....");
				}

				if (loadingProg == 39)
				{
					loadingProg = 0;
				}
				else
				{
					loadingProg++;
				}

				ImGui::SetWindowFontScale(DirectXRenderer::textScale / 2);
				ImGui::Text(DirectXRenderer::ConnectionProg.c_str());
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
				ImGui::SetWindowFontScale(DirectXRenderer::textScale / 2);
				ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_NoScrollbar);
				{
					ImGui::SetWindowFontScale(DirectXRenderer::textScale / 2);
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
											ImGui::TextUnformatted(CChat::chatData[i].message[h].text.c_str());
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
							if (InputBuf[0] == L'/' && CChat::CommandProcessor(InputBuf)) {}
							else 
							{
								std::string message = InputBuf;
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
								RakNet::RakString msg(message.c_str());

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
	std::cout << "DirectXRenderer init" << std::endl;
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
	swapChainDesc.Windowed = /*TRUE*/ ((GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? TRUE : FALSE;

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