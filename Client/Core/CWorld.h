#pragma once

class CWorld {
private:
	struct IPL
	{
		std::wstring	ipl;
		bool			enabled;
		bool			defaultState;
	};

public:
	static std::vector<IPL> g_IPLs;

	static void		Initialize();
	static void		Destroy();

	static void		LoadIPL(std::wstring ipl);
	static void		UnloadIPL(std::wstring ipl);

	static void		LoadModel(const std::wstring model);
	static void		LoadModel(const int model);
};