#ifndef __CCHAT_H__
#define __CCHAT_H__

class CChat {
private:
	struct Message {
		bool newline = false;
		float red = 1.0f;
		float green = 1.0f;
		float blue = 1.0f;
		std::wstring text;
	};

	struct chatPool {
		int messageid;

		int authorid;
		std::wstring author;
		std::vector<Message> message;

		time_t timestamp;
		bool used = false;
	};
public:
	// Limits
	static int MaxLines;
	static int MaxHistory;

	static bool ScrollToBottom;

	// Rendering
	static bool InputOpen;
	static int CurrentRow;
	static int LatestId;

	static void					AddChatMessage(const std::wstring message);
	static void					ClearChat();
	static std::vector<Message> formatMessage(std::wstring message);
	static const int			CommandProcessor(std::wstring command);

	static std::vector<chatPool> chatData;
};
#endif