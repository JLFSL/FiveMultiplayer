#include "stdafx.h"

namespace API {
	const char *Server::ThisNamespace = "API::Server";

	void Server::PrintMessage(const std::string message)
	{
		std::cout << "[" << ThisNamespace << "] " << message << std::endl;
	}
}
