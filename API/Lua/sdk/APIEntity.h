#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace Entity
		{
			/// <summary>
			/// Destroys/Removes a entity from the server
			/// </summary>
			/// <param name="entity">The entity you wish to destroy.</param>
			DLL_PUBLIC_I void Destroy(int entity);

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
			/// <param name="position">The position you wish to set the entity at.</param>
			/// <returns></returns>
			DLL_PUBLIC_I void SetPosition(int entity, CVector3 position);

			/// <summary>
			/// Gets the quaternion of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to get the quaternion off.</param>
			/// <returns name="quaternion">The CVector4 'quaternion' of the entity</returns>
			DLL_PUBLIC_I CVector4 GetQuaternion(int entity);

			/// <summary>
			/// Sets the quaternion of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to set the quaternion off.</param>
			/// <param name="quaternion">The quaternion you wish to set the entity at.</param>
			/// <returns></returns>
			DLL_PUBLIC_I void SetQuaternion(int entity, CVector4 quaternion);

			/// <summary>
			/// Gets the rotation of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to get the rotation off.</param>
			/// <returns name="rotation">The CVector3 rotation of the entity</returns>
			DLL_PUBLIC_I CVector3 GetRotation(int entity);

			/// <summary>
			/// Sets the rotation of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to set the rotation off.</param>
			/// <param name="rotation">The rotation you wish to set they entity at.</param>
			/// <returns></returns>
			DLL_PUBLIC_I void SetRotation(int entity, CVector3 rotation);
			
		}
	}
#ifdef __cplusplus
}
#endif