#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class SpaceGame : public errera::Game {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};

public:
	SpaceGame() = default;

	bool Initialize() override;

	void Update(float dt) override;

	void Draw(class errera::Renderer& renderer) override;

	void OnPlayerDeath();

	void Shutdown() override;
	
private:
	void SpawnEnemy();

private:
	GameState _gameState = GameState::Initialize;
	float _enemySpawnTimer{ 0 };
	float _ringChargeTimer{ 0 };
	float _stateTimer{ 0 };

	std::shared_ptr<errera::Font> _titleFont;
	std::shared_ptr<errera::Font> _uiFont;

	std::unique_ptr<errera::Text> _titleText;
	std::unique_ptr<errera::Text> _scoreText;
	std::unique_ptr<errera::Text> _livesText;
	std::unique_ptr<errera::Text> _ringChargeText;
};