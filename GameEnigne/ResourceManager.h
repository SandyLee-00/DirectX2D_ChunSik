#pragma once
#include "headers.h"

class GraphicsEngine;

class ResourceManager
{
private:
	GraphicsEngine* grapicsEngine;
	std::map<std::string, int> imageMap;

public:
	ResourceManager();
	~ResourceManager();

	void Initalize(GraphicsEngine* _graphicsEngine);

	void LoadImage(const std::string& _key, const std::wstring& _path);
	int GetImageId(const std::string& _key);
};

