#pragma once

#include "../Core/Components/Mesh.h"
#include "../Core/Components/Material.h"
#include "Texture.h"

#include <map>

class Resource
{
public:
	virtual ~Resource() = default;
};

class ResourceManager 
{
public:
	ResourceManager();
	~ResourceManager();

	void Init();
	void Shutdown();

	void Load();
	void Unload();

	Texture* LoadMesh(const std::string& path, const std::string& name);
	Texture* LoadTexture(const std::string& path, const std::string& name);
	Texture* LoadMaterial(const std::string& path, const std::string& name);

	Mesh* CreateMesh(const std::string& name);
	Texture* CreateTexture(const std::string& name);
	Material* CreateMaterial(const std::string& name);

	Mesh* GetMesh(const std::string name);
	Texture* GetTexture(const std::string& name);
	Material* GetMaterial(const std::string& name);

private:
	std::map<std::string, std::shared_ptr<Resource>> m_Resources;
	// std::map<std::string, std::shared_ptr<Mesh>> Meshes;
	// std::map<std::string, std::shared_ptr<Texture>> Textures;
	// std::map<std::string, std::shared_ptr<Material>> Materials;
};
