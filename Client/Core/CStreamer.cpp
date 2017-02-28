#include "stdafx.h"

CStreamer::CStreamer()
{
	MaxPlayers = 40;
	PlayerCount = 0;

	MaxVehicles = 50;
	VehicleCount = 0;

	MaxObjects = 400; // The plan is to have about 1000 objects
	ObjectCount = 0;
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
	if (g_Core && g_Core->GetNetworkManager()->g_ConnectionState == 2)
	{
		if (!g_Entities.empty())
		{
			float curDis = 100.0f;
			while (curDis < 1000.0f)
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

				curDis += 100.0f;
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
							if (g_Players[index].IsCreated() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Players[index].GetPosition()) > (/*streamed[i].distance +*/ 1000.0f))
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
							if (g_Vehicles[index].IsCreated() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Vehicles[index].GetPosition()) >(/*streamed[i].distance +*/ 1000.0f))
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
							if (g_Objects[index].IsCreated() && CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Objects[index].GetPosition()) >(/*streamed[i].distance +*/ 1000.0f))
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
					std::cout << std::endl << "[CStreamer::StreamOut] Found Invalid entity" << std::endl;
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
				std::cout << std::endl << "[CStreamer::ForceStreamOut] Found Invalid entity" << std::endl;
				break;
			}
		}

		streamed.shrink_to_fit();

		PlayerCount = 0;
		VehicleCount = 0;
		ObjectCount = 0;
	}
}