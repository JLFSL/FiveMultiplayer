#include "stdafx.h"

CStreamer::CStreamer()
{
	MaxPlayers = 40;
	PlayerCount = 0;

	MaxVehicles = 50;
	VehicleCount = 0;

	MaxObjects = 400;
	ObjectCount = 0;
}

CStreamer::~CStreamer()
{

}

void CStreamer::Start()
{
	CStreamer streamer;
	streamer.Pulse();
}

void CStreamer::Pulse()
{
	//while (true)
	//{
		if (g_Core && g_Core->GetNetworkManager()->g_ConnectionState == 2)
		{
			if (!g_Entities.empty())
			{
				float curDis = 100.0f;
				while (curDis < 4000.0f)
				{
					/*
						Stream IN
					*/
					for (int i = 0; i < g_Entities.size(); i++)
					{
						switch (g_Entities[i].GetType())
						{
						case CServerEntity::Type::Player:
							if (PlayerCount < MaxPlayers)
							{
								if (g_Entities[i].GetPEntity())
								{
									if (!g_Entities[i].GetPEntity()->IsCreated())
									{
										if (CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Entities[i].GetPEntity()->GetPosition()) < curDis)
										{
											if (g_Entities[i].GetPEntity()->GetId() != g_Core->GetLocalPlayer()->GetId())
											{
												g_Entities[i].GetPEntity()->CreatePed();
												PlayerCount++;

												streamedObject newObj;
												newObj.entity = i;
												newObj.distance = CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Entities[i].GetPEntity()->GetPosition());

												streamed.push_back(newObj);
											}
										}
									}
								}
							}
							break;
						case CServerEntity::Type::Vehicle:
							if (VehicleCount < MaxVehicles)
							{
								if (g_Entities[i].GetVEntity())
								{

								}
							}
							break;
						case CServerEntity::Type::Object:
							if (ObjectCount < MaxObjects)
							{
								if (g_Entities[i].GetOEntity())
								{
									if (!g_Entities[i].GetOEntity()->IsCreated())
									{
										if (CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Entities[i].GetOEntity()->GetPosition()) < curDis)
										{
											std::cout << "Streaming in object " << g_Entities[i].GetOEntity()->GetEntity() << std::endl;
											if (g_Entities[i].GetOEntity()->CreateObject())
											{
												ObjectCount++;

												streamedObject newObj;
												newObj.entity = i;
												newObj.distance = CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Entities[i].GetOEntity()->GetPosition());

												streamed.push_back(newObj);
											}
										}
									}
								}
							}
							break;
						default:
							std::cout << std::endl << "[CStreamer::Pulse] Found Invalid entity" << std::endl;
							break;
						}
					}

					curDis += 100.0f;
				}

				if (!streamed.empty())
				{
					for (int i = 0; i < streamed.size(); i++)
					{
						switch (g_Entities[streamed[i].entity].GetType())
						{
						case CServerEntity::Type::Player:
							if (g_Entities[streamed[i].entity].GetPEntity())
							{
								if (CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Entities[streamed[i].entity].GetPEntity()->GetPosition()) > (streamed[i].distance + 50.0f))
								{
									g_Entities[streamed[i].entity].GetPEntity()->Delete();

									streamed.erase(streamed.begin() + i);
								}
							}
							else
							{
								streamed.erase(streamed.begin() + i);
							}
							break;
						case CServerEntity::Type::Vehicle:
							if (g_Entities[streamed[i].entity].GetVEntity())
							{

							}
							else
							{
								streamed.erase(streamed.begin() + i);
							}
							break;
						case CServerEntity::Type::Object:
							if (g_Entities[streamed[i].entity].GetOEntity())
							{
								if (CVector3::Distance(g_Core->GetLocalPlayer()->GetPos(), g_Entities[streamed[i].entity].GetOEntity()->GetPosition()) > (streamed[i].distance + 50.0f))
								{
									g_Entities[streamed[i].entity].GetOEntity()->Delete();

									streamed.erase(streamed.begin() + i);
								}
							}
							else
							{
								streamed.erase(streamed.begin() + i);
							}
							break;
						default:
							std::cout << std::endl << "[CStreamer::Pulse] Found Invalid entity" << std::endl;
							break;
						}
					}

					streamed.shrink_to_fit();
				}
			}
		}
		else if(!streamed.empty())
		{
			for (int i = 0; i < streamed.size(); i++)
			{
				streamed.erase(streamed.begin() + i);
			}
			streamed.shrink_to_fit();
		}
	//}
}