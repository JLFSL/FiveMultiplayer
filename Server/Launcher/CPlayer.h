#pragma once

class CPlayerEntity {
private:
	unsigned long m_ulLastSyncSent;
public:
	CPlayerEntity();
	~CPlayerEntity();

	bool Create() { return true; }
	bool Destroy() { return true; }

	void Pulse();
};