#include"DataManager.hpp"
ConfigManager::ConfigManager(ConstructorToken token):
	Singleton<ConfigManager>(token)
{ }
SaveManager::SaveManager(ConstructorToken token) :
	Singleton<SaveManager>(token)
{ }
PlantPropertyManager::PlantPropertyManager(ConstructorToken token) :
	Singleton<PlantPropertyManager>(token)
{ }
ZombiePropertyManager::ZombiePropertyManager(ConstructorToken token) :
	Singleton<ZombiePropertyManager>(token)
{ }
ResourceManager::ResourceManager(ConstructorToken token):
	Singleton<ResourceManager>(token)
{ }
auto ResourceManager::LoadResources(const std::filesystem::path& resourceRoot) -> void {
	this->LoadResources(resourceRoot / "manifest.json", resourceRoot);
}
auto ResourceManager::LoadResources(const std::filesystem::path& manifestPath, const std::filesystem::path& resourceRoot) -> void {
	this->LoadData(manifestPath);
	ResourceManifest manifest = this->Data();
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>>textures;
	std::unordered_map<std::string, std::unique_ptr<sf::Music>>musics;
	std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>soundBuffers;
	for (const auto& [id, hash] : manifest.Textures) {
		std::filesystem::path filePath = resourceRoot / hash;
		std::unique_ptr<sf::Texture>texture = std::make_unique<sf::Texture>();
		if (!texture->loadFromFile(filePath)) {
			throw std::runtime_error(fmt::format("Failed to load texture: {}", filePath.string()));
		}
		textures.emplace(id, std::move(texture));
	}
	for (const auto& [id, hash] : manifest.Musics) {
		std::filesystem::path filePath = resourceRoot / hash;
		std::unique_ptr<sf::Music>music = std::make_unique<sf::Music>();
		if (!music->openFromFile(filePath)) {
			throw std::runtime_error(fmt::format("Failed to load music: {}", filePath.string()));
		}
		musics.emplace(id, std::move(music));
	}
	for (const auto& [id, hash] : manifest.SoundBuffers) {
		std::filesystem::path filePath = resourceRoot / hash;
		std::unique_ptr<sf::SoundBuffer>soundBuffer = std::make_unique<sf::SoundBuffer>();
		if (!soundBuffer->loadFromFile(filePath)) {
			throw std::runtime_error(fmt::format("Failed to load sound buffer: {}", filePath.string()));
		}
		soundBuffers.emplace(id, std::move(soundBuffer));
	}
	this->Textures = std::move(textures);
	this->Musics = std::move(musics);
	this->SoundBuffers = std::move(soundBuffers);
}
auto ResourceManager::GetTexture(const std::string& id)const -> const sf::Texture& {
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>>::const_iterator it = this->Textures.find(id);
	if (it == this->Textures.end()) {
		throw std::out_of_range(fmt::format("Texture not found: {}", id));
	}
	return *it->second;
}
auto ResourceManager::GetMusic(const std::string& id) -> sf::Music& {
	std::unordered_map<std::string, std::unique_ptr<sf::Music>>::const_iterator it = this->Musics.find(id);
	if (it == this->Musics.end()) {
		throw std::out_of_range(fmt::format("Music not found: {}", id));
	}
	return *it->second;
}
auto ResourceManager::GetMusic(const std::string& id)const -> const sf::Music& {
	std::unordered_map<std::string, std::unique_ptr<sf::Music>>::const_iterator it = this->Musics.find(id);
	if (it == this->Musics.end()) {
		throw std::out_of_range(fmt::format("Music not found: {}", id));
	}
	return *it->second;
}
auto ResourceManager::GetSoundBuffer(const std::string& id)const -> const sf::SoundBuffer& {
	std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>::const_iterator it = this->SoundBuffers.find(id);
	if (it == this->SoundBuffers.end()) {
		throw std::out_of_range(fmt::format("Sound buffer not found: {}", id));
	}
	return *it->second;
}
[[nodiscard]] auto ResourceManager::Contains(const std::string& id)const noexcept -> const bool {
	return this->Textures.contains(id) || this->Musics.contains(id) || this->SoundBuffers.contains(id);
}