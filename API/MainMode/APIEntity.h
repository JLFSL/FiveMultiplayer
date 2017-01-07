#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace Entity
		{
			/// <summary>
			/// Gets the position of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to get the position off.</param>
			/// <returns name="position">The CVector3 position of the entity</returns>
			DLL_PUBLIC_I CVector3 GetPosition(int entity);

			/// <summary>
			/// Sets the position of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to set the position off.</param>
			/// <param name="position">The position you wish to set they entity off.</param>
			/// <returns></returns>
			DLL_PUBLIC_I void SetPosition(int entity, CVector3 position);
			
		}
	}
#ifdef __cplusplus
}
#endif