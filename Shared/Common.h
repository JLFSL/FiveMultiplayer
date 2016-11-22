// Modification Information
#define INFO_GAME			"Grand Theft Auto 5"
#define INFO_NAME			"Five Multiplayer"
#define INFO_NAME_SHORT		"FiveMP"
#define INFO_VERSION		"0.1b RC6"

#ifdef WIN32
#define LIBRARY_EXTENSION ".dll"
#else
#define LIBRARY_EXTENSION ".so"
#endif

#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

#define SAFE_DELETE(memory) if(memory) { delete memory; memory = NULL; }