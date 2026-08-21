#pragma once
#include"common.hpp"
#include"Singleton.hpp"
#include"JsonDataManager.hpp"
#include"Data.hpp"
class ConfigManager final :public Singleton<ConfigManager>, public JsonDataManager<ConfigData> {
public:
	friend class Singleton<ConfigManager>;
private:
	explicit ConfigManager(ConstructorToken token);
	~ConfigManager()override = default;
};
class SaveManager final :public Singleton<SaveManager>, public JsonDataManager<SaveData> {
public:
	friend class Singleton<SaveManager>;
private:
	explicit SaveManager(ConstructorToken token);
	~SaveManager()override = default;
};
class PlantPropertyManager final :
	public Singleton<PlantPropertyManager>, public JsonDataManager<std::vector<PlantProperty>> {
public:
	friend class Singleton<PlantPropertyManager>;
private:
	explicit PlantPropertyManager(ConstructorToken token);
	~PlantPropertyManager()override = default;
};
class ZombiePropertyManager final :
	public Singleton<ZombiePropertyManager>, public JsonDataManager<std::vector<ZombieProperty>> {
public:
	friend class Singleton<ZombiePropertyManager>;
private:
	explicit ZombiePropertyManager(ConstructorToken token);
	~ZombiePropertyManager()override = default;
};
class ResourceManager final :
	public Singleton<ResourceManager>, private JsonDataManager<ResourceManifest> {
public:
	friend class Singleton<ResourceManager>;
private:
	explicit ResourceManager(ConstructorToken token);
	~ResourceManager()override = default;
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>>Textures;
	std::unordered_map<std::string, std::unique_ptr<sf::Music>>Musics;
	std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>SoundBuffers;
public:
	auto LoadResources(const std::filesystem::path& resourceRoot) -> void;
	auto LoadResources(const std::filesystem::path& manifestPath, const std::filesystem::path& resourceRoot) -> void;
	[[nodiscard]] auto GetTexture(const std::string& id)const -> const sf::Texture&;
	[[nodiscard]] auto GetMusic(const std::string& id) -> sf::Music&;
	[[nodiscard]] auto GetMusic(const std::string& id)const -> const sf::Music&;
	[[nodiscard]] auto GetSoundBuffer(const std::string& id)const -> const sf::SoundBuffer&;
	[[nodiscard]] auto Contains(const std::string& id)const noexcept -> const bool;
};