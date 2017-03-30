#include "stdafx.h"

namespace API
{
	namespace Checkpoints
	{
		void OnEntityEnterCheckpoint(void *Instance, const int checkpoint, const int entity) 
		{
			if (Instance)
			{
				typedef void(*API_OnEntityEnterCheckpoint_t)(int, int);
#ifdef WIN32
				API_OnEntityEnterCheckpoint_t API_OnEntityEnterCheckpoint = (API_OnEntityEnterCheckpoint_t)::GetProcAddress((HMODULE)Instance, "API_OnEntityEnterCheckpoint");
#else
				API_OnEntityEnterCheckpoint_t API_OnEntityEnterCheckpoint = (API_OnEntityEnterCheckpoint_t)dlsym(Instance, "API_OnEntityEnterCheckpoint");
#endif
				API_OnEntityEnterCheckpoint(checkpoint, entity);
			}
		}

		void OnEntityExitCheckpoint(void *Instance, const int checkpoint, const int entity)
		{
			if (Instance)
			{
				typedef void(*API_OnEntityExitCheckpoint_t)(int, int);
#ifdef WIN32
				API_OnEntityExitCheckpoint_t API_OnEntityExitCheckpoint = (API_OnEntityExitCheckpoint_t)::GetProcAddress((HMODULE)Instance, "API_OnEntityExitCheckpoint");
#else
				API_OnEntityExitCheckpoint_t API_OnEntityExitCheckpoint = (API_OnEntityExitCheckpoint_t)dlsym(Instance, "API_OnEntityExitCheckpoint");
#endif
				API_OnEntityExitCheckpoint(checkpoint, entity);
			}
		}
	}
}