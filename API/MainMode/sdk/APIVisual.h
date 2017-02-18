#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace Visual
		{
			/// <summary>
			/// Sends a notification message that displays above the game minimap to all clients.
			/// </summary>
			/// <param name="message">The message of the notification</param>
			/// <param name="pic">Picture to display (pastebin.com/XdpJVbHz)</param>
			/// <param name="icontype">The icon type to use (iconTypes: 1 : Chat Box, 2 : Email, 3 : Add Friend Request, 4 : Nothing, 5 : Nothing, 6 : Nothing, 7 : Right Jumping Arrow, 8 : RP Icon, 9 : $ Icon)</param>
			/// <param name="sender">The sender is the very top header. This can be any string.</param>
			/// <param name="subject">The subject is the header under the sender.</param>
			/// <returns></returns>
			DLL_PUBLIC_I void ShowMessageAboveMap(const std::string message, const std::string pic, int icontype, const std::string sender, const std::string subject);

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
			DLL_PUBLIC_I void ShowMessageAboveMapToPlayer(const int entity, const std::string message, const std::string pic, int icontype, const std::string sender, const std::string subject);
		}
	}
#ifdef __cplusplus
}
#endif