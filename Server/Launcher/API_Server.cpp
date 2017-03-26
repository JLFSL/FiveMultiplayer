#include "stdafx.h"

namespace API {
	const char *Server::ThisNamespace = "API::Server";

	void Server::PrintMessage(const std::wstring message)
	{
		std::wcout << "[" << ThisNamespace << "] " << message.c_str() << std::endl;
	}
}
