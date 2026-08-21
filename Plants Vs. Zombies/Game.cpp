#include"Game.hpp"
Game::Game(ConstructorToken token) :
	Singleton<Game>(token)
{
	auto& configManager = ConfigManager::Initialize();
	auto& saveManager = SaveManager::Initialize();
	auto& plantPropertyManager = PlantPropertyManager::Initialize();
	auto& zombiePropertyManager = ZombiePropertyManager::Initialize();
	auto& resourceManager = ResourceManager::Initialize();
	auto& sceneManager = SceneManager::Initialize();
	const std::filesystem::path resDirectory = std::filesystem::path{ "res" };
	configManager.LoadData(resDirectory / "configs.json");
	saveManager.LoadData(resDirectory / "saves.json");
	plantPropertyManager.LoadData(resDirectory / "plantsProperties.json");
	zombiePropertyManager.LoadData(resDirectory / "zombiesProperties.json");
	resourceManager.LoadResources(resDirectory);
	this->Window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode({ configManager.Data().Window.ResolutionHeight,configManager.Data().Window.ResolutionWidth }),
		configManager.Data().Window.Title
	);
}
Game::~Game() = default;
auto Game::Save()->void {
	auto& configManager = ConfigManager::Instance();
	auto& saveManager = SaveManager::Instance();
	configManager.SaveData();
	saveManager.SaveData();
}
auto Game::Update()->void {
	
}
auto Game::Draw()->void {

}
auto Game::TestResources()->void {
	auto& resourceManager = ResourceManager::Instance();
	const sf::Texture& texture = resourceManager.GetTexture("peashooter");
	sf::Music& music = resourceManager.GetMusic("menu_scene_bgm");
	const sf::SoundBuffer& soundBuffer = resourceManager.GetSoundBuffer("card_click");
	sf::Sprite sprite(texture);
	sf::Sound sound(soundBuffer);
	music.setLooping(true);
	music.play();
	sound.play();
	while (this->Window->isOpen()) {
		while (const std::optional event = this->Window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				this->Window->close();
			}
		}
		this->Window->clear();
		this->Window->draw(sprite);
		this->Window->display();
	}
}