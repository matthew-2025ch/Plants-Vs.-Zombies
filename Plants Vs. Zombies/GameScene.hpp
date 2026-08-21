#pragma once
#include"common.hpp"
class GameScene {
public:
	GameScene(const GameScene&) = delete;
	auto operator=(const GameScene&)->GameScene & = delete;
	virtual~GameScene() = default;
	virtual auto onEnter() -> void = 0;
	virtual auto onExit() -> void = 0;
	virtual auto handleEvent(const sf::Event& event) -> void = 0;
	virtual auto update(sf::Time deltaTime) -> void = 0;
	virtual auto draw(sf::RenderTarget& target)const -> void = 0;
protected:
	GameScene() = default;
};