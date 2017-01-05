#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace Entity
		{
			/// <summary>
			/// Sends a notification message that displays above the game minimap to all clients.
			/// </summary>
			/// <param name="entity">The entity you wish to get the position off.</param>
			/// <returns name="position">The CVector3 position of the entity</returns>
			DLL_PUBLIC_I CVector3 GetPosition(int entity);
			
		}
	}
#ifdef __cplusplus
}
#endif