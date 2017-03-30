#pragma once

namespace API
{
	namespace Checkpoints
	{
		void OnEntityEnterCheckpoint(void *Instance, const int checkpoint, const int entity);
		void OnEntityExitCheckpoint(void *Instance, const int checkpoint, const int entity);
	}
}
