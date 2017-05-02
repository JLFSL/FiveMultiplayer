#ifndef __APIENTITY_H__
#define __APIENTITY_H__
extern "C" {
	namespace API
	{
		class Entity
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static void Destroy(const int entity);

			DLL_PUBLIC static const CVector3 GetPosition(const int entity);
			DLL_PUBLIC static void SetPosition(const int entity, const CVector3 position);
			DLL_PUBLIC static const CVector3 GetRotation(const int entity);
			DLL_PUBLIC static void SetRotation(const int entity, const CVector3 rotation);

			// NPC & Player
			DLL_PUBLIC static const PedComponent GetPedComponent(const int entity, const int componentid);
			DLL_PUBLIC static void SetPedComponent(const int entity, const int componentid, const PedComponent component);
			DLL_PUBLIC static const PedHeadBlend GetPedHeadBlend(const int entity);
			DLL_PUBLIC static void SetPedHeadBlend(const int entity, const PedHeadBlend headblend);
			DLL_PUBLIC static const PedHeadOverlay GetPedHeadOverlay(const int entity, const int index);
			DLL_PUBLIC static void SetPedHeadOverlay(const int entity, const int index, const PedHeadOverlay overlay);
			DLL_PUBLIC static const PedProp GetPedProp(const int entity, const int index);
			DLL_PUBLIC static void SetPedProp(const int entity, const int index, const PedProp prop);
			DLL_PUBLIC static const float GetPedFaceFeature(const int entity, const int index);
			DLL_PUBLIC static void SetPedFaceFeature(const int entity, const int index, const float scale);

			DLL_PUBLIC static const float GetViewDistance(const int entity);
			DLL_PUBLIC static void SetViewDistance(const int entity, const float distance);

			DLL_PUBLIC static const std::vector<int> GetEntities(const int type);
		};
	}
}
#endif