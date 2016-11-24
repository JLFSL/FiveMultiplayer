#include "stdafx.h"

HMODULE _hmoduleDLL;

static eGameState* 				m_gameState;
static uint64_t					m_worldPtr;
static BlipList*				m_blipList;
static NativeRegistration**		m_registrationTable;

using namespace Memory;

/*
TEMP INPUT FUNCTION
*/
#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000
bool isKeyPressedOnce(bool& bIsPressed, DWORD vk)
{
	if (IsKeyPressed(vk))
	{
		if (bIsPressed == false)
		{
			bIsPressed = true;
			return true;
		}
	}
	else if (bIsPressed == true)
	{
		bIsPressed = false;
	}
	return false;
}

void onTickNative()
{
	if (!*m_gameState == GameStatePlaying) return;

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PLAYER::IS_PLAYER_PLAYING(player)) return;

	Vehicle playerVeh = NULL;

	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);


	//Increase wanted level.
	static bool bMultiply = false;
	if (isKeyPressedOnce(bMultiply, VK_MULTIPLY))
	{
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5)
		{
			PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, FALSE);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
		}
	}

	//Decrease wanted level.
	static bool bSubtract = false;
	if (isKeyPressedOnce(bSubtract, VK_SUBTRACT))
	{
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) != 0)
		{
			PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) - 1, FALSE);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
		}
	}

}

/* Start Hooking */

void Hooking::Start(HMODULE hmoduleDLL)
{
	_hmoduleDLL = hmoduleDLL;
	Logger::Init(hmoduleDLL);
	FindPatterns();
	if (!InitializeHooks()) Cleanup();
}

/* Hooks */

// Originals
extern "C"
{
	static UINT(WINAPI *orig_ResetWriteWatch)(LPVOID lpBaseAddress, SIZE_T dwRegionSize) = ResetWriteWatch;
}

// Detoured
UINT WINAPI my_ResetWriteWatch(LPVOID lpBaseAddress, SIZE_T dwRegionSize)
{
	onTickNative();
	return orig_ResetWriteWatch(lpBaseAddress, dwRegionSize);
}

// Initialization
bool Hooking::InitializeHooks()
{
	bool returnVal = TRUE;

	// init minhook
	if (MH_Initialize() != MH_OK) {
		Logger::Error("MinHook failed to initialize");
		returnVal = FALSE;
	}

	// init reset write watch
	if (MH_CreateHook(&ResetWriteWatch, &my_ResetWriteWatch, reinterpret_cast<void**>(&orig_ResetWriteWatch)) != MH_OK || (MH_EnableHook(&ResetWriteWatch) != MH_OK)) {
		Logger::Error("Failed to hook ResetWriteWatch");
		returnVal = FALSE;
	}

	return returnVal;
}

/* Pattern Scanning */

void Hooking::FailPatterns(const char* name, pattern ptn)
{
	Logger::Error("finding %s (%s)");
	Cleanup();
}

static bool gameLoading = false;

static void WaitForInitLoopWrap()
{
	// certain executables may recheck activation after connection, and want to perform this state change after 12 - ignore those cases
	// draw_menu_line("WaitForInitLoopWrap called", 15.0f, 50.0f, 570.0f, 6.0f, 5.0f, false, false, false); //drawrect set to true
	//*g_initState = MapInitState(6);

	//WaitForInitLoop();
	if (!gameLoading) {
		//*g_initState = 7;

		//LoadGameNow(0);
		gameLoading = true;
	}
}

void Hooking::FindPatterns()
{
	auto p_gameState = pattern("83 3D ? ? ? ? ? 8A D9 74 0A");
	auto p_worldPtr = pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
	auto p_blipList = pattern("4C 8D 05 ? ? ? ? 0F B7 C1");
	auto p_nativeTable = pattern("76 61 49 8B 7A 40 48 8D 0D");
	auto p_gameLogos = pattern("70 6C 61 74 66 6F 72 6D 3A");
	auto p_gameLegals = pattern("72 1F E8 ? ? ? ? 8B 0D");
	auto p_modelCheck = pattern("48 85 C0 0F 84 ? ? ? ? 8B 48 50");
	auto p_modelSpawn = pattern("48 8B C8 FF 52 30 84 C0 74 05 48");
	//auto p_skipToSP = pattern("33 C9 E8 ? ? ? ? 8B 0D ? ? ? ? 48 8B 5C 24 ? 8D 41 FC 83 F8 01 0F 47 CF 89 0D ? ? ? ?");

	char * c_location = nullptr;
	//int(*LoadGameNow)(char);

	// Executable Base Address
	DEBUGMSG("baseAddr\t\t 0x%p", get_base());

	// Executable End Address
	DEBUGMSG("endAddr\t\t 0x%p", get_base() + get_size());

	// Get game state
	c_location = p_gameState.count(1).get(0).get<char>(2);
	c_location == nullptr ? FailPatterns("gameState", p_gameState) : m_gameState = reinterpret_cast<decltype(m_gameState)>(c_location + *(int32_t*)c_location + 5);

	// Skip game logos
	Memory::putVP<uint8_t>(p_gameLogos.count(1).get(0).get<void>(0), 0xC3);

	// Wait for legals
	DWORD ticks = GetTickCount();
	while (*m_gameState != GameStateLicenseShit || GetTickCount() < ticks + 5000) Sleep(50);

	// Skip game legals
	Memory::nop(p_gameLegals.count(1).get(0).get<void>(0), 2);

	// Wait for landing page
	ticks = GetTickCount();
	while (*m_gameState != GameStateMainMenu || GetTickCount() < ticks + 5000) Sleep(50);

	// Load Singleplayer
	//char* func = pattern("33 C9 E8 ? ? ? ? 8B 0D ? ? ? ? 48 8B 5C 24 ? 8D 41 FC 83 F8 01 0F 47 CF 89 0D ? ? ? ?").count(1).get(0).get<char>(2);
	//c_location = p_skipToSP.count(1).get(0).get<char>(2);
	//set_call(&LoadGameNow, c_location);

	//Sleep(5000);

	// Get native registration table
	c_location = p_nativeTable.count(1).get(0).get<char>(9);
	c_location == nullptr ? FailPatterns("native registration Table", p_nativeTable) : m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_location + *(int32_t*)c_location + 4);

	// Get world pointer
	c_location = p_worldPtr.count(1).get(0).get<char>(0);
	c_location == nullptr ? FailPatterns("world Pointer", p_worldPtr) : m_worldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

	// Get blip list
	c_location = p_blipList.count(1).get(0).get<char>(0);
	c_location == nullptr ? FailPatterns("blip List", p_blipList) : m_blipList = reinterpret_cast<decltype(m_blipList)>(c_location + *reinterpret_cast<int*>(c_location + 3) + 7);

	// Bypass online model requests block
	Memory::nop(p_modelCheck.count(1).get(0).get<void>(0), 24);

	// Bypass is player model allowed to spawn checks
	Memory::nop(p_modelSpawn.count(1).get(0).get<void>(8), 2);

	DEBUGMSG("Initializing natives");
	CrossMapping::initNativeMap();

	// Check if game is ready
	Logger::Msg("Checking if game is ready...");

	bool start = false;

	while (!*m_gameState == GameStatePlaying) {
		if (!start) {
			//LoadGameNow(0);
			start = !start;
		}

		Sleep(100);
	}
	Logger::Msg("Game ready");
}

Hooking::NativeHandler Hooking::GetNativeHandler(uint64_t origHash) {

	uint64_t newHash = CrossMapping::MapNative(origHash);
	if (newHash == 0) {
		return nullptr;
	}

	NativeRegistration * table = m_registrationTable[newHash & 0xFF];

	for (; table; table = table->nextRegistration)
	{
		for (uint32_t i = 0; i < table->numEntries; i++)
		{
			if (newHash == table->hashes[i])
			{
				return table->handlers[i];
			}

		}
	}

	return nullptr;
}

/* Clean Up */
void Hooking::Cleanup()
{
	Logger::Msg("CleanUp: FiveMP Hook");

	MH_DisableHook(&ResetWriteWatch);
	MH_Uninitialize();
	FreeLibraryAndExitThread(_hmoduleDLL, 0);
}