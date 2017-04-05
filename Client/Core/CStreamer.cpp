#include "stdafx.h"

std::vector<CStreamer::streamedObject> CStreamer::streamed;

float CStreamer::MaxRange = 1000.0f;

int CStreamer::MaxPlayers = 40;		// The max visable players to be shown
int CStreamer::PlayerCount = 0;	// The current count of visable players
float CStreamer::PlayerRange = 1000.0f;	// Should the 'MaxPlayers' be reached it'll store the range it reached at that point here for the streamingout to check.

int CStreamer::MaxVehicles = 50;
int CStreamer::VehicleCount = 0;
float CStreamer::VehicleRange = 1000.0f;

int CStreamer::MaxObjects = 500;
int CStreamer::ObjectCount = 0;
float CStreamer::ObjectRange = 1000.0f;

int CStreamer::MaxNpcs = 20;
int CStreamer::NpcCount = 0;
float CStreamer::NpcRange = 1000.0f;

void CStreamer::Start()
{
	CStreamer streamer;
	streamer.Pulse();
}

void CStreamer::Pulse()
{
	StreamObjectsIn(CLocalPlayer::GetPosition());
	StreamVehiclesIn(CLocalPlayer::GetPosition());
	StreamPlayersIn(CLocalPlayer::GetPosition());
	StreamOtherIn(CLocalPlayer::GetPosition());

	StreamOut(CLocalPlayer::GetPosition());
}

void CStreamer::StreamObjectsIn(CVector3 position)
{
	if (CNetworkManager::g_ConnectionState == CONSTATE_COND)
	{
		if (!g_Entities.empty())
		{
			float curDis = 50.0f;
			// Objects have First priority
			while (curDis < MaxRange)
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (ObjectCount < MaxObjects && curDis < g_Entities[i].GetViewDistance())
					{
						switch (g_Entities[i].GetType())
						{
						case CServerEntity::Type::Object:
							for (int index = 0; index < g_Objects.size(); index++)
							{
								if (g_Objects[index].GetId() == g_Entities[i].GetId())
								{
									const float distance = CVector3::Distance(position, g_Objects[index].GetPosition());
									if (!g_Objects[index].IsCreated() && distance < curDis)
									{
										if (g_Objects[index].CreateObject())
										{
											if (ObjectCount == (MaxObjects - 1))
												ObjectRange = distance;
											else
												ObjectRange = 1000.0f;

											ObjectCount++;

											streamedObject newObj;
											newObj.entity = g_Entities[i].GetId();
											newObj.distance = distance;

											streamed.push_back(newObj);
										}
									}
									break;
								}
							}
							break;
						}
					}
					else
						break;
				}

				curDis += 50.0f;
			}
		}
	}
}

void CStreamer::StreamVehiclesIn(CVector3 position)
{
	if (CNetworkManager::g_ConnectionState == CONSTATE_COND)
	{
		if (!g_Entities.empty())
		{
			float curDis = 50.0f;
			while (curDis < MaxRange)
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (VehicleCount < MaxVehicles && curDis < g_Entities[i].GetViewDistance())
					{
						switch (g_Entities[i].GetType())
						{
						case CServerEntity::Type::Vehicle:
							for (int index = 0; index < g_Vehicles.size(); index++)
							{
								if (g_Vehicles[index].GetId() == g_Entities[i].GetId())
								{
									const float distance = CVector3::Distance(position, g_Vehicles[index].GetPosition());
									if (!g_Vehicles[index].IsCreated() && distance < curDis)
									{
										if (g_Vehicles[index].CreateVehicle())
										{
											if (VehicleCount == (MaxVehicles - 1))
												VehicleRange = distance;
											else
												VehicleRange = 1000.0f;

											VehicleCount++;

											streamedObject newObj;
											newObj.entity = g_Entities[i].GetId();
											newObj.distance = distance;

											streamed.push_back(newObj);
										}
									}
									break;
								}
							}
							break;
						}
					}
					else
						break;
				}

				curDis += 50.0f;
			}
		}
	}
}


void CStreamer::StreamPlayersIn(CVector3 position)
{
	if (CNetworkManager::g_ConnectionState == CONSTATE_COND)
	{
		if (!g_Entities.empty())
		{
			float curDis = 50.0f;
			while (curDis < MaxRange)
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (PlayerCount < MaxPlayers && curDis < g_Entities[i].GetViewDistance())
					{
						switch (g_Entities[i].GetType())
						{
						case CServerEntity::Type::Player:
							for (int index = 0; index < g_Players.size(); index++)
							{
								if (g_Players[index].GetId() == g_Entities[i].GetId())
								{
									const float distance = CVector3::Distance(position, g_Players[index].GetPosition());
									if (!g_Players[index].IsCreated() && g_Players[index].GetId() != CLocalPlayer::GetId() && distance < curDis)
									{
										/*
										If we reach the 'max' for this type we will want to bring the range down for this type so object between X & 1000 have the chance to get streamed in.
										This isn't full proof and there might still be the possibility of entities not getting streamed in.
										*/
										if (PlayerCount == (MaxPlayers - 1))
											PlayerRange = distance;
										else
											PlayerRange = 1000.0f;

										g_Players[index].CreatePed();
										PlayerCount++;

										streamedObject newObj;
										newObj.entity = g_Entities[i].GetId();
										newObj.distance = distance;

										streamed.push_back(newObj);
									}
									break;
								}
							}
						}
						break;
					}
					else
						break;
				}

				curDis += 50.0f;
			}
		}
	}
}


void CStreamer::StreamOtherIn(CVector3 position)
{
	if (CNetworkManager::g_ConnectionState == CONSTATE_COND)
	{
		if (!g_Entities.empty())
		{
			float curDis = 50.0f;
			while (curDis < MaxRange)
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					switch (g_Entities[i].GetType())
					{
					case CServerEntity::Type::NPC:
						if (NpcCount < MaxNpcs < g_Entities[i].GetViewDistance())
						{
							for (int index = 0; index < g_Npcs.size(); index++)
							{
								if (g_Npcs[index].GetId() == g_Entities[i].GetId())
								{
									const float distance = CVector3::Distance(position, g_Npcs[index].GetPosition());
									if (!g_Npcs[index].IsCreated() && distance < curDis)
									{
										if (g_Npcs[index].CreateNpc())
										{
											if (NpcCount == (MaxNpcs - 1))
												NpcRange = distance;
											else
												NpcRange = 1000.0f;

											NpcCount++;

											streamedObject newObj;
											newObj.entity = g_Entities[i].GetId();
											newObj.distance = distance;

											streamed.push_back(newObj);
										}
									}
									break;
								}
							}
						}
						break;
					}
				}

				curDis += 50.0f;
			}
		}
	}
}


void CStreamer::StreamOut(CVector3 position)
{
	if (CNetworkManager::g_ConnectionState == CONSTATE_COND)
	{
		if (!streamed.empty())
		{
			for (int i = 0; i < streamed.size(); i++)
			{
				switch (g_Entities[streamed[i].entity].GetType())
				{
				case CServerEntity::Type::Player:
					for (int index = 0; index < g_Players.size(); index++)
					{
						if (g_Players[index].GetId() == streamed[i].entity)
						{
							const float distance = CVector3::Distance(position, g_Players[index].GetPosition());
							if (g_Players[index].IsCreated() && (distance > (PlayerRange + 10.0f) || distance > g_Entities[i].GetViewDistance() + 10.0f))
							{
								g_Players[index].Delete();

								streamed.erase(streamed.begin() + i);
								PlayerCount--;
							}
							break;
						}
					}
					break;
				case CServerEntity::Type::Vehicle:
					for (int index = 0; index < g_Vehicles.size(); index++)
					{
						if (g_Vehicles[index].GetId() == streamed[i].entity)
						{
							const float distance = CVector3::Distance(position, g_Vehicles[index].GetPosition());
							if (g_Vehicles[index].IsCreated() && (distance > (VehicleRange + 10.0f) || distance > g_Entities[i].GetViewDistance() + 10.0f))
							{
								g_Vehicles[index].Delete();

								streamed.erase(streamed.begin() + i);
								VehicleCount--;
							}
							break;
						}
					}
					break;
				case CServerEntity::Type::Object:
					for (int index = 0; index < g_Objects.size(); index++)
					{
						if (g_Objects[index].GetId() == streamed[i].entity)
						{
							const float distance = CVector3::Distance(position, g_Objects[index].GetPosition());
							if (g_Objects[index].IsCreated() && (distance > (ObjectRange + 10.0f) || distance > g_Entities[i].GetViewDistance() + 10.0f))
							{
								g_Objects[index].Delete();

								streamed.erase(streamed.begin() + i);
								ObjectCount--;
							}
							break;
						}
					}
					break;
				case CServerEntity::Type::NPC:
					for (int index = 0; index < g_Npcs.size(); index++)
					{
						if (g_Npcs[index].GetId() == streamed[i].entity)
						{
							const float distance = CVector3::Distance(position, g_Npcs[index].GetPosition());
							if (g_Npcs[index].IsCreated() && (distance >(NpcRange + 10.0f) || distance > g_Entities[i].GetViewDistance() + 10.0f))
							{
								g_Npcs[index].Delete();

								streamed.erase(streamed.begin() + i);
								NpcCount--;
							}
							break;
						}
					}
					break;
				default:
					streamed.erase(streamed.begin() + i);
					//std::cout << "[CStreamer::StreamOut] Found Invalid entity " << g_Entities[i].GetId() << std::endl;
					break;
				}
			}

			streamed.shrink_to_fit();
		}
	}
	else if (!streamed.empty())
	{
		for (int i = 0; i < streamed.size(); i++)
		{
			streamed.erase(streamed.begin() + i);
		}
		streamed.shrink_to_fit();
	}
}

void CStreamer::ForceStreamOut()
{
	if (!streamed.empty())
	{
		for (int i = 0; i < streamed.size(); i++)
		{
			switch (g_Entities[streamed[i].entity].GetType())
			{
			case CServerEntity::Type::Player:
				for (int index = 0; index < g_Players.size(); index++)
				{
					if (g_Players[index].GetId() == streamed[i].entity)
					{
						if (g_Players[index].IsCreated())
							g_Players[index].Delete();

						streamed.erase(streamed.begin() + i);
						PlayerCount--;
						break;
					}
				}
				break;
			case CServerEntity::Type::Vehicle:
				for (int index = 0; index < g_Vehicles.size(); index++)
				{
					if (g_Vehicles[index].GetId() == streamed[i].entity)
					{
						if (g_Vehicles[index].IsCreated())
							g_Vehicles[index].Delete();

						streamed.erase(streamed.begin() + i);
						VehicleCount--;
						break;
					}
				}
				break;
			case CServerEntity::Type::Object:
				for (int index = 0; index < g_Objects.size(); index++)
				{
					if (g_Objects[index].GetId() == streamed[i].entity)
					{
						if (g_Objects[index].IsCreated())
							g_Objects[index].Delete();

						streamed.erase(streamed.begin() + i);
						ObjectCount--;
						break;
					}
				}
				break;
			case CServerEntity::Type::NPC:
				for (int index = 0; index < g_Npcs.size(); index++)
				{
					if (g_Npcs[index].GetId() == streamed[i].entity)
					{
						if (g_Npcs[index].IsCreated())
							g_Npcs[index].Delete();

						streamed.erase(streamed.begin() + i);
						NpcCount--;
						break;
					}
				}
				break;
			default:
				std::cout << "[CStreamer::ForceStreamOut] Found Invalid entity " << g_Entities[i].GetId() << std::endl;
				break;
			}
		}

		streamed.shrink_to_fit();

		PlayerCount = 0;
		VehicleCount = 0;
		ObjectCount = 0;
		NpcCount = 0;
	}
}