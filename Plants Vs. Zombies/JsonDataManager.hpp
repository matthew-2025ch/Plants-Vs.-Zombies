#pragma once
#include"JsonManager.hpp"
template<typename T>
class JsonDataManager :public JsonManager {
private:
	std::filesystem::path FilePath;
	std::optional<T>data;
	auto RequireLoaded()const -> void {
		if (!this->data) {
			throw std::logic_error("Data is not loaded. Please call LoadData() or Create() first.");
		}
	}
public:
	auto LoadData(const std::filesystem::path& filePath) -> void {
		T temp = this->ReadJson(filePath).template get<T>();
		this->FilePath = filePath;
		this->data = std::move(temp);
	}
	auto CreateData(const std::filesystem::path& filePath, T initialData = {}) -> void {
		this->FilePath = filePath;
		this->data = std::move(initialData);
	}
	auto SaveData()const -> void {
		this->RequireLoaded();
		const nlohmann::json json = *this->data;
		this->WriteJson(this->FilePath, json);
	}
	[[nodiscard]] auto IsLoaded()const noexcept -> bool {
		return this->data.has_value();
	}
	[[nodiscard]] auto Data() -> T& {
		this->RequireLoaded();
		return this->data.value();
	}
	[[nodiscard]] auto Data()const -> const T& {
		this->RequireLoaded();
		return this->data.value();
	}
protected:
	JsonDataManager() = default;
	~JsonDataManager()override = default;
};