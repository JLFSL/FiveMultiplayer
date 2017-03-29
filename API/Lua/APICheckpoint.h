#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Checkpoint
		{
		public:
			/// <summary>
			/// Creates a Checkpoint of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the npc you wish to create</param>
			/// <param name="position">The position you wish to create the npc at</param>
			/// <param name="heading">The heading you wish to have the npc facing</param>
			/// <returns name="entity">The npc server entity id</returns>
			DLL_PUBLIC_I static const int Create(CVector3 position, CVector3 pointto, const int type, const float radius, Color color, const int reserved);
		};
	}
#ifdef __cplusplus
}
#endif