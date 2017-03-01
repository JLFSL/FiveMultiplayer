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
}

void CStreamer::Start()
{
	CStreamer streamer;
	streamer.Pulse();
}

void CStreamer::Pulse()
{
	StreamIn(g_Core->GetLocalPlayer()->GetPos());
	StreamOut(g_Core->GetLocalPlayer()->GetPos());
}

void CStreamer::StreamIn(CVector3 position)
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
							for(int index = 0; index < g_Players.size(); index++)
							{
								if (g_Players[index].GetId() == g_Entities[i].GetId())
								{
									if (!g_Players[index].IsCreated() && g_Players[index].GetId() != g_Core->GetLocalPlayer()->GetId() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Players[index].GetPosition()) < curDis)
									{
										/*
											If we reach the 'max' for this type we will want to bring the range down for this type so object between X & 1000 have the chance to get streamed in.
											This isn't full proof and there might still be the possibility of entities not getting streamed in.
										*/
										if (PlayerCount == (MaxPlayers - 1))
											PlayerRange = CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Players[index].GetPosition());
										else
											PlayerRange = 1000.0f;

										g_Players[index].CreatePed();
										PlayerCount++;

										streamedObject newObj;
										newObj.entity = g_Entities[i].GetId();
										newObj.distance = CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Players[index].GetPosition());

										streamed.push_back(newObj);
									}
									break;
								}
							}
						}
						break;
					case CServerEntity::Type::Vehicle:
						if (VehicleCount < MaxVehicles)
						{
							for (int index = 0; index < g_Vehicles.size(); index++)
							{
								if (g_Vehicles[index].GetId() == g_Entities[i].GetId())
								{
									if (!g_Vehicles[index].IsCreated() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Vehicles[index].GetPosition()) < curDis)
									{
										if (g_Vehicles[index].CreateVehicle())
										{
											if (VehicleCount == (MaxVehicles - 1))
												VehicleRange = CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Vehicles[index].GetPosition());
											else
												VehicleRange = 1000.0f;

											VehicleCount++;

											streamedObject newObj;
											newObj.entity = g_Entities[i].GetId();
											newObj.distance = CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Vehicles[index].GetPosition());

											streamed.push_back(newObj);
										}
									}
									break;
								}
							}
						}
						break;
					case CServerEntity::Type::Object:
						if (ObjectCount < MaxObjects)
						{
							for (int index = 0; index < g_Objects.size(); index++)
							{
								if (g_Objects[index].GetId() == g_Entities[i].GetId())
								{
									if (!g_Objects[index].IsCreated() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Objects[index].GetPosition()) < curDis)
									{
										if (g_Objects[index].CreateObject())
										{
											if (ObjectCount == (MaxObjects - 1))
												ObjectRange = CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Objects[index].GetPosition());
											else
												ObjectRange = 1000.0f;

											ObjectCount++;

											streamedObject newObj;
											newObj.entity = g_Entities[i].GetId();
											newObj.distance = CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Objects[index].GetPosition());

											streamed.push_back(newObj);
										}
									}
									break;
								}
							}
						}
						break;
					default:
						std::cout << "[CStreamer::StreamIn] Found Invalid entity" << std::endl;
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
	if (g_Core && g_Core->GetNetworkManager()->g_ConnectionState == 2)
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
							if (g_Players[index].IsCreated() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Players[index].GetPosition()) > (PlayerRange + 10.0f))
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
							if (g_Vehicles[index].IsCreated() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Vehicles[index].GetPosition()) > (VehicleRange + 10.0f))
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
							if (g_Objects[index].IsCreated() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Objects[index].GetPosition()) > (ObjectRange + 10.0f))
							{
								g_Objects[index].Delete();

								streamed.erase(streamed.begin() + i);
								ObjectCount--;
							}
							break;
						}
					}
					break;
				default:
					std::cout << "[CStreamer::StreamOut] Found Invalid entity" << std::endl;
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
			default:
				std::cout << "[CStreamer::ForceStreamOut] Found Invalid entity" << std::endl;
				break;
			}
		}

		streamed.shrink_to_fit();

		PlayerCount = 0;
		VehicleCount = 0;
		ObjectCount = 0;
	}
}