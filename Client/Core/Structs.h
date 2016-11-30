#pragma once
#include <cstddef>

struct NativeRegistration
{
	NativeRegistration * nextRegistration;
	Hooking::NativeHandler handlers[7];
	uint32_t numEntries;
	uint64_t hashes[7];
};