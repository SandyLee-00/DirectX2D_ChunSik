#pragma once
#include "headers.h"
#include <filesystem>
class PathManager
{
private:
	std::filesystem::path nowPath; 
	std::filesystem::path headPath; 
	std::wstring resDirName;

public:
	PathManager();
	~PathManager();

	void Initalize();
	std::wstring GetResourcePath(const std::wstring& _string);
};

