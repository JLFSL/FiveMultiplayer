#pragma once

namespace API
{
	class Checkpoint {
	private:
		static const char *ThisNamespace;

	public:
		DLL_PUBLIC static const int Create(const CVector3 position, const CVector3 pointto, const int type, const float radius, const Color color, const int reserved);
		DLL_PUBLIC static const void Show(const int checkpointenity, const int playerentity);
		DLL_PUBLIC static const void Hide(const int checkpointenity, const int playerentity);
	};
}