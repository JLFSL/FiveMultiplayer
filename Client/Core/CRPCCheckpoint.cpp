#include "stdafx.h"

void CRPCCheckpoint::Create(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, type, reserved;
	CVector3 position;
	CVector3 pointto;
	float radius;
	Color color;

	bitStream->Read(entity);
	bitStream->Read(position.fX);
	bitStream->Read(position.fY);
	bitStream->Read(position.fZ);
	bitStream->Read(pointto.fX);
	bitStream->Read(pointto.fY);
	bitStream->Read(pointto.fZ);
	bitStream->Read(type);
	bitStream->Read(radius);
	bitStream->Read(color.Red);
	bitStream->Read(color.Green);
	bitStream->Read(color.Blue);
	bitStream->Read(color.Alpha);
	bitStream->Read(reserved);


	CCheckpointEntity newCp;

	newCp.Create(entity, position, pointto, type, radius, color, reserved);
	g_Checkpoints.push_back(newCp);
}

void CRPCCheckpoint::Show(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;

	bitStream->Read(entity);

	for (int i = 0; i < g_Checkpoints.size(); i++) {
		if (g_Checkpoints[i].GetId() == entity) {
			return g_Checkpoints[i].Show();
		}
	}
}

void CRPCCheckpoint::Hide(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;

	bitStream->Read(entity);

	for (int i = 0; i < g_Checkpoints.size(); i++) {
		if (g_Checkpoints[i].GetId() == entity) {
			return g_Checkpoints[i].Hide();
		}
	}
}