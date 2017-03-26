#include "stdafx.h"

CStreamer::CStreamer()
{
	/*
		Set-up Defaults
	*/
	MaxRange = 1000.0f;

	MaxPlayers = 40;
	PlayerCount = 0;
	PlayerRange = 1000;

	MaxVehicles = 50;
	VehicleCount = 0;
	VehicleRange = 1000.0f;

	MaxObjects = 500;		// The plan is to have about 1000 objects
	ObjectCount = 0;
	ObjectRange = 1000.0f;

	MaxNpcs = 20;
	NpcCount = 0;
	NpcRange = 1000.0f;
}

void CStreamer::Start()
{
	CStreamer streamer;
	streamer.Pulse();
}

void CStreamer::Pulse()
{
	StreamObjectsIn(g_Core->GetLocalPlayer()->GetPos());
	StreamVehiclesIn(g_Core->GetLocalPlayer()->GetPos());
	StreamPlayersIn(g_Core->GetLocalPlayer()->GetPos());
	StreamOtherIn(g_Core->GetLocalPlayer()->GetPos());

	StreamOut(g_Core->GetLocalPlayer()->GetPos());
}

void CStreamer::StreamObjectsIn(CVector3 position)
{
	if (g_Core && g_Core->GetNetworkManager()->g_ConnectionState == CONSTATE_COND)
	{
		if (!g_Entities.empty())
		{
			float curDis = 50.0f;
			// Objects have First priority
			while (curDis < MaxRange)
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (ObjectCount < MaxObjects)
					{
						switch (g_Entities[i].GetType())
						{
						case CServerEntity::Type::Object:
							for (int index = 0; index < g_Objects.size(); index++)
							{
								if (g_Objects[index].GetId() == g_Entities[i].GetId())
								{
									if (!g_Objects[index].IsCreated() && CVector3::Distance(position, g_Objects[index].GetPosition()) < curDis)
									{
										if (g_Objects[index].CreateObject())
										{
											if (ObjectCount == (MaxObjects - 1))
												ObjectRange = CVector3::Distance(position, g_Objects[index].GetPosition());
											else
												ObjectRange = 1000.0f;

											ObjectCount++;

											streamedObject newObj;
											newObj.entity = g_Entities[i].GetId();
											newObj.distance = CVector3::Distance(position, g_Objects[index].GetPosition());

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
	if (g_Core && g_Core->GetNetworkManager()->g_ConnectionState == CONSTATE_COND)
	{
		if (!g_Entities.empty())
		{
			float curDis = 50.0f;
			while (curDis < MaxRange)
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (VehicleCount < MaxVehicles)
					{
						switch (g_Entities[i].GetType())
						{
						case CServerEntity::Type::Vehicle:
							for (int index = 0; index < g_Vehicles.size(); index++)
							{
								if (g_Vehicles[index].GetId() == g_Entities[i].GetId())
								{
									if (!g_Vehicles[index].IsCreated() && CVector3::Distance(position, g_Vehicles[index].GetPosition()) < curDis)
									{
										if (g_Vehicles[index].CreateVehicle())
										{
											if (VehicleCount == (MaxVehicles - 1))
												VehicleRange = CVector3::Distance(position, g_Vehicles[index].GetPosition());
											else
												VehicleRange = 1000.0f;

											VehicleCount++;

											streamedObject newObj;
											newObj.entity = g_Entities[i].GetId();
											newObj.distance = CVector3::Distance(position, g_Vehicles[index].GetPosition());

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
	if (g_Core && g_Core->GetNetworkManager()->g_ConnectionState == CONSTATE_COND)
	{
		if (!g_Entities.empty())
		{
			float curDis = 50.0f;
			while (curDis < MaxRange)
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (PlayerCount < MaxPlayers)
					{
						switch (g_Entities[i].GetType())
						{
						case CServerEntity::Type::Player:
							for (int index = 0; index < g_Players.size(); index++)
							{
								if (g_Players[index].GetId() == g_Entities[i].GetId())
								{
									if (!g_Players[index].IsCreated() && g_Players[index].GetId() != g_Core->GetLocalPlayer()->GetId() && CVector3::Distance(position, g_Players[index].GetPosition()) < curDis)
									{
										/*
										If we reach the 'max' for this type we will want to bring the range down for this type so object between X & 1000 have the chance to get streamed in.
										This isn't full proof and there might still be the possibility of entities not getting streamed in.
										*/
										if (PlayerCount == (MaxPlayers - 1))
											PlayerRange = CVector3::Distance(position, g_Players[index].GetPosition());
										else
											PlayerRange = 1000.0f;

										g_Players[index].CreatePed();
										PlayerCount++;

										streamedObject newObj;
										newObj.entity = g_Entities[i].GetId();
										newObj.distance = CVector3::Distance(position, g_Players[index].GetPosition());

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
	if (g_Core && g_Core->GetNetworkManager()->g_ConnectionState == CONSTATE_COND)
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
					case CServerEntity::Type::Player:
						if (PlayerCount < MaxPlayers)
						{
							for (int index = 0; index < g_Players.size(); index++)
							{
								if (g_Players[index].GetId() == g_Entities[i].GetId())
								{
									if (!g_Players[index].IsCreated() && g_Players[index].GetId() != g_Core->GetLocalPlayer()->GetId() && CVector3::Distance(position, g_Players[index].GetPosition()) < curDis)
									{
										/*
										If we reach the 'max' for this type we will want to bring the range down for this type so object between X & 1000 have the chance to get streamed in.
										This isn't full proof and there might still be the possibility of entities not getting streamed in.
										*/
										if (PlayerCount == (MaxPlayers - 1))
											PlayerRange = CVector3::Distance(position, g_Players[index].GetPosition());
										else
											PlayerRange = 1000.0f;

										g_Players[index].CreatePed();
										PlayerCount++;

										streamedObject newObj;
										newObj.entity = g_Entities[i].GetId();
										newObj.distance = CVector3::Distance(position, g_Players[index].GetPosition());

										streamed.push_back(newObj);
									}
									break;
								}
							}
						}
						break;
					case CServerEntity::Type::NPC:
						if (NpcCount < MaxNpcs)
						{
							for (int index = 0; index < g_Npcs.size(); index++)
							{
								if (g_Npcs[index].GetId() == g_Entities[i].GetId())
								{
									if (!g_Npcs[index].IsCreated() && CVector3::Distance(position, g_Npcs[index].GetPosition()) < curDis)
									{
										if (g_Npcs[index].CreateNpc())
										{
											if (NpcCount == (MaxNpcs - 1))
												NpcRange = CVector3::Distance(position, g_Npcs[index].GetPosition());
											else
												NpcRange = 1000.0f;

											NpcCount++;

											streamedObject newObj;
											newObj.entity = g_Entities[i].GetId();
											newObj.distance = CVector3::Distance(position, g_Npcs[index].GetPosition());

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
	if (g_Core && g_Core->GetNetworkManager()->g_ConnectionState == CONSTATE_COND)
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
							if (g_Players[index].IsCreated() && CVector3::Distance(position, g_Players[index].GetPosition()) > (PlayerRange + 10.0f))
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
							if (g_Vehicles[index].IsCreated() && CVector3::Distance(position, g_Vehicles[index].GetPosition()) > (VehicleRange + 10.0f))
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
							if (g_Objects[index].IsCreated() && CVector3::Distance(position, g_Objects[index].GetPosition()) > (ObjectRange + 10.0f))
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
							if (g_Npcs[index].IsCreated() && CVector3::Distance(position, g_Npcs[index].GetPosition()) >(ObjectRange + 10.0f))
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
					std::cout << "[CStreamer::StreamOut] Found Invalid entity " << g_Entities[i].GetId() << std::endl;
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