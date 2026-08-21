#pragma once
#include"common.hpp"
#include"Data.hpp"
#include"GameScene.hpp"
class MenuScene :public GameScene {
public:
	explicit MenuScene(const SceneData& data);
	auto onEnter() -> void override;
	auto onExit() -> void override;
	auto handleEvent(const sf::Event& event) -> void override;
	auto update(sf::Time deltaTime) -> void override;
	auto draw(sf::RenderTarget& target)const -> void override;
};