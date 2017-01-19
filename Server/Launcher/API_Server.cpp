#include "stdafx.h"

namespace API {
	namespace Server {
		char *ThisNamespace = "API::Server";

		int PrintMessage(const std::string message)
		{
			std::cout << "[" << ThisNamespace << "] " << message << std::endl;
			return 1;
		}
	}
}
