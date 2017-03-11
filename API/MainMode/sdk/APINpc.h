#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class NPC
		{
		public:
			/// <summary>
			/// Creates a NPC of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the npc you wish to create</param>
			/// <param name="position">The position you wish to create the npc at</param>
			/// <param name="heading">The heading you wish to have the npc facing</param>
			/// <returns name="entity">The npc server entity id</returns>
			DLL_PUBLIC_I static const int Create(const std::string model, const CVector3 position, const float heading);
		};
	}
#ifdef __cplusplus
}
#endif