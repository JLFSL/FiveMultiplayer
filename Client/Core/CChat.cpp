#include "stdafx.h"

int CChat::MaxLines = 15;
int CChat::MaxHistory = 100;

bool CChat::ScrollToBottom = true;

bool CChat::InputOpen = false;
int CChat::CurrentRow = 0;
int CChat::LatestId = 0;

std::vector<CChat::chatPool> CChat::chatData;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void CChat::AddChatMessage(const std::string message)
{
	chatPool addto;

	std::vector<Message> _messages = CChat::formatMessage(message.c_str());

	for (int i = 0; i < _messages.size(); i++)
	{
		if (!_messages.empty())
			addto.message.push_back(_messages[i]);
	}

	std::string temp;
	for (int i = 0; i < addto.message.size(); i++)
	{
		temp.append(addto.message[i].text);
		if ((ImGui::CalcTextSize(temp.c_str()).x / 2) * DirectXRenderer::textScale > (800 * DirectXRenderer::windowScale))
		{
			addto.message[i].newline = true;
			temp.empty();
			temp.append(addto.message[i].text);
		}
	}

	addto.used = true;
	chatData.push_back(addto);

	if (chatData.size() >= MaxHistory)
	{
		chatData.erase(chatData.begin());
		chatData.shrink_to_fit();
	}

	ScrollToBottom = true;
}

void CChat::ClearChat()
{
	if (!chatData.empty())
	{
		for (int i = (chatData.size() - 1); i > -1; i--)
		{
			chatData[i] = {};
			chatData.erase(chatData.begin() + i);
		}
	}
}

std::vector<CChat::Message> CChat::formatMessage(std::string message)
{
	std::vector<Message> messages;
	Message _message;

	for (unsigned int i = 0; i < message.size() * sizeof(wchar_t); i++)
	{
		/*
		Format Code
		*/
		if (message.data()[i] == '{')
		{
			if (i + 7 < message.size() * sizeof(wchar_t))
			{
				if (message.data()[i + 7] == '}')
				{
					//Push the last message into the stack and erase the message for the new one if not the start of the message
					if (i != 0)
					{
						messages.push_back(_message);
						_message.text.erase(_message.text.begin(), _message.text.end());
						_message.newline = false;
					}

					//Grab the Hex Color
					std::string sHex = "0x";
					for (unsigned int j = i + 1; j < i + 7; j++)
					{
						sHex.push_back(message[j]);
					}
					//Convert the Hex to long
					unsigned long value = std::stol(sHex, nullptr, 0);

					//Get the RBG values and convert them to floats [0.0:1.0]
					if (value != NULL)
					{
						_message.red = ((value >> 16) & 0xff) / 255.0;
						_message.green = ((value >> 8) & 0xff) / 255.0;
						_message.blue = ((value) & 0xff) / 255.0;
					}

					//Move the loop forward past the color code
					i = i + 7;
				}
			}
		}
		/*
		New Line Code
		*/
		else if (message.data()[i] == '\n')
		{
			//Push the last message into the vector and erase the message for the next one if not the start of the message
			if (i != 0)
			{
				messages.push_back(_message);
				_message.text.erase(_message.text.begin(), _message.text.end());
			}

			_message.newline = true;
		}
		/*
		Push the char data to the text
		*/
		else
		{
			_message.text.push_back(message.data()[i]);

			//If end of string push the _message in to the vector
			if (i == message.size() * sizeof(wchar_t) - 1)
			{
				messages.push_back(_message);
				_message.text.erase(_message.text.begin(), _message.text.end());
			}
		}
	}

	return messages;
}

const int CChat::CommandProcessor(std::string command)
{
	std::vector<std::string> params = split(command, ' ');
	command = params[0];
	params.erase(params.begin());

	if (!command.compare("/connect") && CNetworkManager::g_ConnectionState == CONSTATE_DISC)
	{
		if (params[0] != "")
		{
			if (params[1] == "")
				params[1] = "2322";

			CNetworkManager::Connect((char *)params[0].c_str(), "default", (int)params[1].c_str());
			CVisual::ShowMessageAboveMap("An error occured while calling the ~r~connect ~w~function", "", 4, "", "");
		}
		return true;
	}

	if (!command.compare("/disconnect"))
	{
		if (CNetworkManager::g_ConnectionState == CONSTATE_COND)
		{
			CNetworkManager::Disconnect();
			CChat::AddChatMessage("{333333}Connection: Disconnected from the server.");
		}
		else
		{
			CVisual::ShowMessageAboveMap("Could not disconnect: ~r~Not connected", "", 4, "", "");
		}
		return true;
	}

	if (!command.compare("/quit"))
	{
		CNetworkManager::Disconnect();
		CNetworkManager::Stop();
		WAIT(10);
		exit(EXIT_SUCCESS);
		return true;
	}

	return false;
}
