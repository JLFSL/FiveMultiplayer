#pragma once

class CInterface
{
public:
	virtual bool OnLoad(int argc, char ** argv) = 0;
	virtual void Process() = 0;
	virtual void OnUnload() = 0;
	virtual void SetActive(bool bActive) = 0;
	virtual bool IsActive() = 0;
};
