#pragma once

#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class PlatformerGame : public errera::Game, public errera::IObserver {
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

	int player1Score = 0;
	int player2Score = 0;
	int round = 0;

	std::string winner;

public:
	PlatformerGame() = default;

	bool Initialize() override;

	void Update(float dt) override;

	void Draw(class errera::Renderer& renderer) override;

	void OnPlayerDeath();

	void OnNotify(const errera::Event& event) override;

	void Shutdown() override;

private:

	void SpawnPlayers();

	void Winscreen();

	void RoundAnnouncer();

private:
	GameState _gameState = GameState::Initialize;
	float _enemySpawnTimer{ 0 };
	float _stateTimer{ 0 };

	std::unique_ptr<errera::Text> _titleText;
	std::unique_ptr<errera::Text> _scoreText;
	std::unique_ptr<errera::Text> _livesText;
};