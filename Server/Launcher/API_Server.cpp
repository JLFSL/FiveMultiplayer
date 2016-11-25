#include "stdafx.h"

namespace API {
	namespace Server {
		char *ThisNamespace = "API::Server";

		int PrintMessage(const char *message)
		{
			cout << "[" << ThisNamespace << "] " << message << endl;
			return 1;
		}
	}
}
