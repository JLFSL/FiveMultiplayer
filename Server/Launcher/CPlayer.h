#pragma once

class CPlayerEntity {
private:
	

public:
	CPlayerEntity();
	~CPlayerEntity();

	bool Create() { return true; }
	bool Destroy() { return true; }

	void Pulse();
};