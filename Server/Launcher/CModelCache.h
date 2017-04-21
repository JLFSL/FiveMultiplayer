#ifndef __CMODELCACHE_H__
#define __CMODELCACHE_H__

class CModelCache
{
public:
	static std::vector<std::wstring> stringModels;
	static std::vector<int> hashModels;

	static void LoadModels(RakNetGUID user);

	static void AddModel(const std::wstring model);
	static void AddModel(const int model);
};

#endif