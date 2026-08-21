#include"JsonManager.hpp"
auto JsonManager::ReadJson(const std::filesystem::path& filePath)const -> nlohmann::json {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error(fmt::format("Failed to open file: {}", filePath.string()));
	}
	try {
		nlohmann::json json;
		file >> json;
		return json;
	}
	catch (const nlohmann::json::exception& e) {
		throw std::runtime_error(fmt::format("Failed to parse JSON File: {}\nReason: {}", filePath.string(), e.what()));
	}
}
auto JsonManager::WriteJson(const std::filesystem::path& filePath, const nlohmann::json& json)const -> void {
	if (filePath.has_parent_path()) {
		std::filesystem::create_directories(filePath.parent_path());
	}
	std::ofstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error(fmt::format("Failed to write JSON file: {}", filePath.string()));
	}
	file << json.dump(4);
	if(!file.good()) {
		throw std::runtime_error(fmt::format("Failed while writing JSON File: {}", filePath.string()));
	}
}