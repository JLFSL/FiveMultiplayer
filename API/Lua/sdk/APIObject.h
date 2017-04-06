#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Object
		{
		public:
			/// <summary>
			/// Creates a object of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the object you wish to create</param>
			/// <param name="position">The position you wish to create the object at</param>
			/// <param name="rotation">The rotation you wish to create the object with</param>
			/// <param name="dynamic">If the object should be dynamic or not. (has physics or not)</param>
			/// <returns name="entity">The objects server entity id</returns>
			DLL_PUBLIC_I static const int Create(const std::wstring model, const CVector3 position, const CVector3 rotation, const bool dynamic);


			/// <summary>
			/// Creates a object of a desired hash of a model name at the position defined
			/// </summary>
			/// <param name="hash">The hash of the model name of the object you wish to create</param>
			/// <param name="position">The position you wish to create the object at</param>
			/// <param name="rotation">The rotation you wish to create the object with</param>
			/// <param name="dynamic">If the object should be dynamic or not. (has physics or not)</param>
			/// <returns name="entity">The objects server entity id</returns>
			DLL_PUBLIC_I static const int Create(const int hash, const CVector3 position, const CVector3 rotation, const bool dynamic);

			/// <summary>
			/// Gets the texture variation of the object entity.
			/// </summary>
			/// <param name="entity">The enity of the objetc you wish to get the texture variation of</param>
			DLL_PUBLIC_I static const int GetTextureVariation(const int entity);

			/// <summary>
			/// Sets the texture variation of the object entity.
			/// </summary>
			/// <param name="entity">The enity of the objetc you wish to set the texture variation of</param>
			/// <param name="textureindex">The texture id/index</param>
			DLL_PUBLIC_I static void SetTextureVariation(const int entity, const int textureindex);
		};
	}
#ifdef __cplusplus
}
#endif