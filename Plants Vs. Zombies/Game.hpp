#pragma once
#include"common.hpp"
#include"Singleton.hpp"
#include"DataManager.hpp"
#include"SceneManager.hpp"
class Game final :public Singleton<Game> {
private:
	friend class Singleton<Game>;

	std::shared_ptr<sf::RenderWindow>Window;
	explicit Game(ConstructorToken token);
	~Game();
public:
	auto Save() -> void;
	auto Update() -> void;
	auto Draw() -> void;
	auto TestResources() -> void;
};
extern Game& game;