#include "stdafx.h"

#define TESTING

bool to_bool(std::string str)
{
	std::locale loc;
	for (std::string::size_type i = 0; i<str.length(); ++i)
		std::cout << std::tolower(str[i], loc);

	std::istringstream is(str);
	bool b;
	is >> std::boolalpha >> b;
	return b;
};

std::vector<Vehicle> vehicles;
std::vector<Object> objects;
std::vector<NPC> npcs;
std::vector<Checkpoint> checkpoints;

// When Plugin gets loaded
extern "C" DLL_PUBLIC bool API_Initialize(void) 
{
	API::Server::PrintMessage(L"Gamemode Initializing...");

	Vehicle newVehicle;
#ifdef TESTING
	newVehicle.Create(L"elegy", CVector3(-3.0f, 6.0f, 73.0f), 10.0f);
	vehicles.push_back(newVehicle);
	newVehicle.Create(L"comet3", CVector3(-6.0f, 8.0f, 73.0f), 10.0f);
	vehicles.push_back(newVehicle);
	newVehicle.Create(L"blazer5", CVector3(-9.0f, 10.0f, 73.0f), 10.0f);
	vehicles.push_back(newVehicle);
	newVehicle.Create(L"voltic2", CVector3(-12.0f, 12.0f, 73.0f), 10.0f);
	vehicles.push_back(newVehicle);
#else
	newVehicle.Create(L"elegy", CVector3(1533.53f, 3282.39f, 52.5f), 195.0f);
	vehicles.push_back(newVehicle);
	newVehicle.Create(L"comet3", CVector3(1527.65f, 3296.66f, 52.5f), 195.0f);
	vehicles.push_back(newVehicle);
	newVehicle.Create(L"blazer5", CVector3(1519.32f, 3280.2f, 52.5f), 195.0f);
	vehicles.push_back(newVehicle);
	newVehicle.Create(L"voltic2", CVector3(1516.84f, 3293.88f, 52.5f), 195.0f);
	vehicles.push_back(newVehicle);
#endif

	API::World::SetTime(13, 0, 0);

	int hour, minute, second;
	API::World::GetTime(&hour, &minute, &second);
	std::cout << "Time: " << hour << ":" << minute << ":" << second << std::endl;

	NPC newNpc;
	Checkpoint newCp;

#ifdef TESTING
	//newNpc.Create(L"s_m_m_movspace_01", CVector3(0.0f, 0.0f, 74.0f), CVector3(0.0f, 0.0f, 90.0f));
	//npcs.push_back(newNpc);

	newCp.Create(CVector3(0.0f, 0.0f, 74.0f), CVector3(0.0f, 0.0f, 124.0f), 1, 5.0f, Color{ 255,0,0,255 }, 0);
	checkpoints.push_back(newCp);
#else
	newNpc.Create(L"s_m_m_movspace_01", CVector3(1527.62f, 3274.39f, 53.0f), CVector3(0.0f, 0.0f, 90.0f));
	npcs.push_back(newNpc);

	newCp.Create(CVector3(1527.62f, 3274.39f, 53.0f), CVector3(1527.62f, 3274.39f, 153.0f), 1, 5.0f, Color{ 255,0,0,255 }, 0);
	checkpoints.push_back(newCp);

	// Load Objects
	Json::Value root;
	Json::Reader reader;

	std::ifstream stream("./maps/objects.json", std::ifstream::binary);
	stream >> root;
	
	if (!reader.parse(stream, root, false))
	{
		// report to the user the failure and their locations in the document.
		std::cout << reader.getFormattedErrorMessages() << std::endl;;
	}
	
	const int objectcount = root["Map"]["Objects"]["MapObject"].size();

	Object newObject;

	for (int i = 0; i < objectcount; i++)
	{
		CVector3 position(
			(float)std::atof(root["Map"]["Objects"]["MapObject"][i]["Position"]["X"].asCString()),
			(float)std::atof(root["Map"]["Objects"]["MapObject"][i]["Position"]["Y"].asCString()),
			(float)std::atof(root["Map"]["Objects"]["MapObject"][i]["Position"]["Z"].asCString())
		);
		
		CVector3 rotation = {
			(float)std::atof(root["Map"]["Objects"]["MapObject"][i]["Rotation"]["X"].asCString()),
			(float)std::atof(root["Map"]["Objects"]["MapObject"][i]["Rotation"]["Y"].asCString()),
			(float)std::atof(root["Map"]["Objects"]["MapObject"][i]["Rotation"]["Z"].asCString()),
		};
		
		newObject.Create(atoi(root["Map"]["Objects"]["MapObject"][i]["Hash"].asCString()), position, rotation, to_bool(root["Map"]["Objects"]["MapObject"][i]["Dynamic"].asCString()));
		newObject.SetTextureVariation(2);
		objects.push_back(newObject);
	}
	// END Load Objects
	
#endif

	API::Server::PrintMessage(L"Gamemode Initialized!");
	return true;
}

// When plugin gets unloaded
extern "C" DLL_PUBLIC bool API_Close(void) 
{
	// Deletes all created vehicles stored in the pool.
	for (int i = 0; i < vehicles.size(); i++)
	{
		vehicles[i].Destroy();
	}
	// Deletes all created vehicles stored in the pool.
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].Destroy();
	}
	// Deletes all created npcs stored in the pool.
	for (int i = 0; i < npcs.size(); i++)
	{
		npcs[i].Destroy();
	}
	// Deletes all created checkpoints stored in the pool.
	for (int i = 0; i < checkpoints.size(); i++)
	{
		checkpoints[i].Destroy();
	}

	std::cout << "close" << std::endl;
	return true;
}

// Every server tick this gets called
extern "C" DLL_PUBLIC bool API_OnTick(void) 
{
	//API::Visual::ShowMessageAboveMap("I don't like people!", "CHAR_DEFAULT", 1, "Jack", "");
	return true;
}

// Player Connecting
extern "C" DLL_PUBLIC bool API_OnPlayerConnecting(const std::string guid)
{
	std::wstringstream oss;
	oss << L"Player connecting with [guid: " << guid.c_str() << L"]";
	API::Server::PrintMessage(oss.str());

	oss.str(std::wstring());
	oss.clear();

	oss << L"~p~A Player is connecting [" << guid.c_str() << L"]";
	API::Visual::ShowMessageAboveMap(oss.str(), L"CHAR_DEFAULT", 1, L"Server", L"Player Joining");
	return true;
}

// Player Connected
extern "C" DLL_PUBLIC bool API_OnPlayerConnected(int entity, int playerid)
{
	std::wstringstream oss;
	oss << L"~g~You Connected! ~o~[~w~ID: " << playerid << L"~o~]";
	API::Visual::ShowMessageAboveMapToPlayer(entity, oss.str().c_str(), L"CHAR_CREATOR_PORTRAITS", 1, L"Server", L"");

	API::Player::SetModel(entity, L"u_m_y_pogo_01");

#ifdef TESTING
	API::Entity::SetPosition(entity, CVector3(0.0f, 0.0f, 73.5f));
#else
	API::Entity::SetPosition(entity, CVector3(1527.62f, 3274.39f, 53.0f));
#endif

	CVector3 position = API::Entity::GetPosition(entity);
	
	oss.str(std::wstring());
	oss.clear();

	oss << L"~p~Position: " << position.x << L" " << position.y << L" " << position.z;
	API::Visual::ShowMessageAboveMapToPlayer(entity, oss.str().c_str(), L"CHAR_CREATOR_PORTRAITS", 5, L"Server", L"Position");

	for (int i = 0; i < checkpoints.size(); i++) {
		checkpoints[i].Show(entity);
	}

	return true;
}

// When a entity enters a checkpoint (only players right now)
extern "C" DLL_PUBLIC void API_OnEntityEnterCheckpoint(int checkpoint, int entity)
{
	API::Server::PrintMessage(L"OnEntityEnterCheckpoint");
}

// When a entity exits a checkpoint (only players right now)
extern "C" DLL_PUBLIC void API_OnEntityExitCheckpoint(int checkpoint, int entity)
{
	API::Server::PrintMessage(L"OnEntityExitCheckpoint");
}

// When a player sends a command
extern "C" DLL_PUBLIC void API_OnPlayerCommand(const int entity, const std::string message)
{
	API::Server::PrintMessage(L"OnPlayerCommand");
}

// When a player sends a message
extern "C" DLL_PUBLIC void API_OnPlayerMessage(const int entity, const std::string message)
{
	API::Server::PrintMessage(L"OnPlayerMessage");

	API::Visual::SendChatMessage(message);
}