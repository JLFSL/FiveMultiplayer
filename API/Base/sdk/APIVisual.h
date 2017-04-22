#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Visual
		{
		public:
			/// <summary>
			/// Sends a notification message that displays above the game minimap to all clients.
			/// </summary>
			/// <param name="message">The message of the notification</param>
			/// <param name="pic">Picture to display (pastebin.com/XdpJVbHz)</param>
			/// <param name="icontype">The icon type to use (iconTypes: 1 : Chat Box, 2 : Email, 3 : Add Friend Request, 4 : Nothing, 5 : Nothing, 6 : Nothing, 7 : Right Jumping Arrow, 8 : RP Icon, 9 : $ Icon)</param>
			/// <param name="sender">The sender is the very top header. This can be any string.</param>
			/// <param name="subject">The subject is the header under the sender.</param>
			/// <returns></returns>
			DLL_PUBLIC_I static void ShowMessageAboveMap(const std::wstring message, const std::wstring pic, const int icontype, const std::wstring sender, const std::wstring subject);

			/// <summary>
			/// Sends a notification message that displays above the game minimap to a specific client.
			/// </summary>
			/// <param name="entity">The entity id of the player you wish to send it too</param>
			/// <param name="message">The message of the notification</param>
			/// <param name="pic">Picture to display (pastebin.com/XdpJVbHz)</param>
			/// <param name="icontype">The icon type to use (iconTypes: 1 : Chat Box, 2 : Email, 3 : Add Friend Request, 4 : Nothing, 5 : Nothing, 6 : Nothing, 7 : Right Jumping Arrow, 8 : RP Icon, 9 : $ Icon)</param>
			/// <param name="sender">The sender is the very top header. This can be any string.</param>
			/// <param name="subject">The subject is the header under the sender.</param>
			/// <returns></returns>
			DLL_PUBLIC_I static void ShowMessageAboveMapToPlayer(const int entity, const std::wstring message, const std::wstring pic, const int icontype, const std::wstring sender, const std::wstring subject);

			/// <summary>
			/// Sends a chat message to all clients.
			/// </summary>
			/// <param name="message">The string of the message</param>
			DLL_PUBLIC_I static void SendChatMessage(const std::string message);

			/// <summary>
			/// Sends a chat message to a client.
			/// </summary>
			/// <param name="entity">The entityid of the player you wish to sedn the message to.</param>
			/// <param name="message">The string of the message</param>
			DLL_PUBLIC_I static void SendChatMessageToPlayer(const int entity, const std::string message);
		};
	}
#ifdef __cplusplus
}
#endif