#pragma once
#include"common.hpp"
struct WindowConfig {
	unsigned int ResolutionWidth = 1280;
	unsigned int ResolutionHeight = 720;
	std::string Title = "Plants vs. Zombies";
	bool Fullscreen = false;
	bool VSync = false;
	unsigned int FrameRateLimit = 60;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
	WindowConfig,
	ResolutionWidth, ResolutionHeight, Title, Fullscreen, VSync, FrameRateLimit
)
struct AudioConfig {
	float MasterVolume = 100.0f;
	float MusicVolume = 80.0f;
	float SFXVolume = 100.0f;
	bool muted = false;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
	AudioConfig,
	MasterVolume, MusicVolume, SFXVolume, muted
)
struct ConfigData {
	WindowConfig Window;
	AudioConfig Audio;
	std::string Language;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
	ConfigData,
	Window, Audio, Language
)
struct SaveData {
	std::string PlayerName = "Player";
	int Coins = 0;
	int Level = 1;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
	SaveData,
	PlayerName, Coins, Level
)
struct ResourceManifest {
	std::unordered_map<std::string, std::string> Textures;
	std::unordered_map<std::string, std::string> Musics;
	std::unordered_map<std::string, std::string> SoundBuffers;
};
inline void from_json(const nlohmann::json& json, ResourceManifest& data) {
	json.at("textures").get_to(data.Textures);
	json.at("musics").get_to(data.Musics);
	json.at("sound_buffers").get_to(data.SoundBuffers);
}
inline void to_json(nlohmann::json& json, const ResourceManifest& data) {
	json = nlohmann::json{
		{"textures", data.Textures},
		{"musics", data.Musics},
		{"sound_buffers", data.SoundBuffers}
	};
}
enum class SceneType { Loading, Menu, ChooseSeed, Battle, Cnt };
enum class PlantType { PeaShooter, Cnt };
enum class ZombieType { Zombie, Cnt };
struct Property {
	std::string Id = "Unknown";
	int Cost = 0;
	int Hp = 0;
};
struct PlantProperty :public Property {
	int AttackInterval = 0; //ms
	int ATK = 0;
	int RechargeTime = 0; //ms
	bool Sleepy = false;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
	PlantProperty,
	Id, Cost, Hp, AttackInterval, RechargeTime, ATK, Sleepy
)
struct ZombieProperty :public Property {
	double Speed = 0.0;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
	ZombieProperty,
	Id, Cost, Hp, Speed
)