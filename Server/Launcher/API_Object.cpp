#include "stdafx.h"

namespace API
{
	namespace Object
	{
		const char *ThisNamespace = "API::Object";

		int CreateObject(std::string model, CVector3 position, CVector4 quaternion, bool dynamic)
		{
			CObjectEntity newObject;
			newObject.Create(model, position, quaternion, dynamic);
			g_Objects.push_back(newObject);

			RakNet::BitStream sData;
			sData.Write(newObject.GetEntity());
			sData.Write(false);
			sData.Write(RakString(model.c_str()));
			sData.Write(position.fX);
			sData.Write(position.fY);
			sData.Write(position.fZ);
			sData.Write(quaternion.fX);
			sData.Write(quaternion.fY);
			sData.Write(quaternion.fZ);
			sData.Write(quaternion.fW);
			sData.Write(dynamic);

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateObject", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

			return newObject.GetEntity();
		}

		int CreateObjectWithHash(int hash, CVector3 position, CVector4 quaternion, bool dynamic)
		{
			CObjectEntity newObject;
			newObject.Create(hash, position, quaternion, dynamic);
			g_Objects.push_back(newObject);

			RakNet::BitStream sData;
			sData.Write(newObject.GetEntity());
			sData.Write(true);
			sData.Write(hash);
			sData.Write(position.fX);
			sData.Write(position.fY);
			sData.Write(position.fZ);
			sData.Write(quaternion.fX);
			sData.Write(quaternion.fY);
			sData.Write(quaternion.fZ);
			sData.Write(quaternion.fW);
			sData.Write(dynamic);

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateObject", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

			return newObject.GetEntity();
		}

		int CreateObjectWithRotation(std::string model, CVector3 position, CVector3 rotation, bool dynamic)
		{
			CVector4 quaternion = CVector4::calculateQuaternion(rotation.fX, rotation.fY, rotation.fZ);

			CObjectEntity newObject;
			newObject.Create(model, position, quaternion, dynamic);
			g_Objects.push_back(newObject);

			RakNet::BitStream sData;
			sData.Write(newObject.GetEntity());
			sData.Write(false);
			sData.Write(RakString(model.c_str()));
			sData.Write(position.fX);
			sData.Write(position.fY);
			sData.Write(position.fZ);
			sData.Write(quaternion.fX);
			sData.Write(quaternion.fY);
			sData.Write(quaternion.fZ);
			sData.Write(quaternion.fW);
			sData.Write(dynamic);

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateObject", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

			return newObject.GetEntity();
		}

		int CreateObjectWithHRotation(int hash, CVector3 position, CVector3 rotation, bool dynamic)
		{
			CVector4 quaternion = CVector4::calculateQuaternion(rotation.fX, rotation.fY, rotation.fZ);

			CObjectEntity newObject;
			newObject.Create(hash, position, quaternion, dynamic);
			g_Objects.push_back(newObject);

			RakNet::BitStream sData;
			sData.Write(newObject.GetEntity());
			sData.Write(true);
			sData.Write(hash);
			sData.Write(position.fX);
			sData.Write(position.fY);
			sData.Write(position.fZ);
			sData.Write(quaternion.fX);
			sData.Write(quaternion.fY);
			sData.Write(quaternion.fZ);
			sData.Write(quaternion.fW);
			sData.Write(dynamic);

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateObject", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

			return newObject.GetEntity();
		}
	}
}
