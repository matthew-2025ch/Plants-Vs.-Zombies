#pragma once
#include"common.hpp"
class JsonManager {
public:
	JsonManager(const JsonManager&) = delete;
	JsonManager(JsonManager&&) = delete;
	auto operator=(const JsonManager&)->JsonManager & = delete;
	auto operator=(JsonManager&&)->JsonManager & = delete;
	virtual ~JsonManager() = default;
protected:
	JsonManager() = default;
	[[nodiscard]] auto ReadJson(const std::filesystem::path& filePath) const -> nlohmann::json;
	auto WriteJson(const std::filesystem::path& filePath, const nlohmann::json& json)const -> void;
};