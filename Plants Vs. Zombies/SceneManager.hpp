#pragma once
#include"common.hpp"
#include"Singleton.hpp"
#include"Data.hpp"
#include"JsonDataManager.hpp"
struct SceneTypeHash {
	auto operator()(SceneType type)const noexcept -> std::size_t {
		return static_cast<std::size_t>(type);
	}
};
class SceneManager final :public Singleton<SceneManager> {
public:
	friend class Singleton<SceneManager>;
private:
	explicit SceneManager(ConstructorToken token);
	~SceneManager()override = default;
};