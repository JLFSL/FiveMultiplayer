#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class CEF
		{
		public:
			/// <summary>
			/// Sets the client's URL
			/// </summary>
			/// <param name="entity">The Hour you wish to set</param>
			/// <param name="url">The Minute you wish to set</param>
			/// <param name="appcode">The Minute you wish to set</param>
			DLL_PUBLIC_I static void LoadURL(const int entity, std::string url, std::string appcode = "", bool remote = false);

			/// <summary>
			/// Sets the World Time
			/// </summary>
			/// <param name="hour">The Hour you wish to set</param>
			/// <param name="minute">The Minute you wish to set</param>
			/// <param name="second">The Second you wish to set</param>
			DLL_PUBLIC_I static void JavaScriptCall(const int entity, std::string call);
		};
	}
#ifdef __cplusplus
}
#endif