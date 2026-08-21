#include"common.hpp"
#include"Logger.hpp"
#include"Game.hpp"
#include"Tools.hpp"
#define Error(content) MessageBoxW(nullptr, content, L"Error", MB_OK | MB_ICONERROR) 
auto main() -> int {
	try {
		Logger::Initialize();
		spdlog::info("Starting Plants vs. Zombies");
		Game& game = Game::Initialize();
		spdlog::info("Game initialized successfully");
		game.TestResources();
		spdlog::info("Game exited normally");
		return EXIT_SUCCESS;
	}
	catch (std::exception& e) {
		spdlog::critical("Unhandled exception: {}", e.what());
		Logger::Flush();
		Error(Tools::UTF82Wide(e.what()).c_str());
		return EXIT_FAILURE;
	}
}