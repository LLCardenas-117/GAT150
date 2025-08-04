#include "SpaceGame.h"

#include "Audio/AudioSystem.h"
#include "Core/Random.h"
#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Player.h"
#include "Renderer/Font.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Input/InputSystem.h"
#include "GameData.h"
#include "ringBlast.h"

#include <vector>

bool SpaceGame::Initialize() {
    _scene = std::make_unique<errera::Scene>(this);

    _titleFont = std::make_shared<errera::Font>();
    _titleFont->Load("arcadeclassic.ttf", 128);

    _uiFont = std::make_shared<errera::Font>();
    _uiFont->Load("arcadeclassic.ttf", 48);

    _titleText = std::make_unique<errera::Text>(_titleFont);
    _scoreText = std::make_unique<errera::Text>(_uiFont);
    _livesText = std::make_unique<errera::Text>(_uiFont);
    _ringChargeText = std::make_unique<errera::Text>(_uiFont);

    return true;
}

void SpaceGame::Update(float dt) {
    switch (_gameState) {
    case SpaceGame::GameState::Initialize:
        _gameState = GameState::Title;
        break;

    case SpaceGame::GameState::Title:
        if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            _gameState = GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
        _score = 0;
        _lives = 3;
        _ring = 0;
        _gameState = GameState::StartLevel;
        break;

    case SpaceGame::GameState::StartLevel:
    {
        _scene->RemoveAllActors();

        // Create Player
        std::shared_ptr<errera::Model> model = std::make_shared<errera::Model>(GameData::playerShipPoints, errera::vec3{ 0, 1, 0 });
        errera::Transform transform{ errera::vec2{ errera::GetEngine().GetRenderer().GetWidth() * 0.5f , errera::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 5 };
        auto player = std::make_unique<Player>(transform, model);
        player->speed = 1000.0f;
        player->rotationRate = 280.0f;
        player->damping = 0.75f;
        player->name = "player";
        player->tag = "player";

        _scene->AddActor(std::move(player));
        _gameState = GameState::Game;
    }
        break;

    case SpaceGame::GameState::Game:
        _enemySpawnTimer -= dt;
        _ringChargeTimer -= dt;

        if (_enemySpawnTimer <= 0) {
            _enemySpawnTimer = 5;

            SpawnEnemy();
        }

        if (_ringChargeTimer <= 0) {
            _ringChargeTimer = 40;

            NewRingCharge(_ring);
        }

        if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_F) && _ring >= 1) {
            Player* player = _scene->GetActorByName<Player>("player");
            if (player) {
                errera::GetEngine().GetAudio().PlaySound("ring-blast");
                std::shared_ptr<errera::Model> ringBlastModel = std::make_shared<errera::Model>(GameData::ringPoints, errera::vec3{ 1.0f, 1.0f, 1.0f });
                errera::vec2 position = player->transform.position + errera::random::onUnitCircle();
                errera::Transform transform{ position, 0, 2.5 };
                std::unique_ptr<ringBlast> ring = std::make_unique<ringBlast>(transform, ringBlastModel);
                ring->damping = 1.5f;
                ring->speed = 300.0f;
                ring->tag = "player";
                ring->lifespan = 3.0f;
                _scene->AddActor(std::move(ring));
                _ring -= 1;
            }
        }

        break;

    case SpaceGame::GameState::PlayerDead:
        _stateTimer -= dt;
		if (_stateTimer <= 0) {
            _lives--;
            if (_lives == 0) {
                _stateTimer = 2;
                _gameState = GameState::GameOver; 
            }
            else { _gameState = GameState::StartLevel; }
		}
        break;

    case SpaceGame::GameState::GameOver:
        _stateTimer -= dt;
        if (_stateTimer <= 0) {
		    _gameState = GameState::Title;
        }
        break;
    }

    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {
        errera::GetEngine().GetTime().SetTimeScale(0.5f);
    }
    else {
        errera::GetEngine().GetTime().SetTimeScale(1.0f);

    }

    _scene->Update(errera::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(errera::Renderer& renderer) {
    if (_gameState == GameState::Title) {
        _titleText->Create(renderer, "Halo Space", errera::vec3{ 0, 1, 0 });
        _titleText->Draw(renderer, renderer.GetHeight() / 3, renderer.GetWidth() / 3);
    }

    if (_gameState == GameState::GameOver) {
        _titleText->Create(renderer, "GAME OVER", errera::vec3{ 1, 0, 0 });
        _titleText->Draw(renderer, renderer.GetHeight() / 3, renderer.GetWidth() / 3);
    }

	_scoreText->Create(renderer, "SCORE " + std::to_string(_score), errera::vec3{1, 1, 1});
	_scoreText->Draw(renderer, 10, 10);

    _livesText->Create(renderer, "LIVES " + std::to_string(_lives), errera::vec3{1, 1, 1});
    _livesText->Draw(renderer,(float)(renderer.GetWidth() - 200), 10);

    _ringChargeText->Create(renderer, "Ring Charges " + std::to_string(_ring), errera::vec3{ 1, 1, 1 });
    _ringChargeText->Draw(renderer, 10, renderer.GetHeight() - 100);

    _scene->Draw(renderer);

	errera::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDeath() {
	_gameState = GameState::PlayerDead;
    _stateTimer = 2;
}

void SpaceGame::Shutdown() {
}

void SpaceGame::SpawnEnemy() {
    Player* player = _scene->GetActorByName<Player>("player");
    if (player) {
        // SAVING CODE FOR ENEMY CODE
        std::shared_ptr<errera::Model> enemyModel = std::make_shared<errera::Model>(GameData::enemyShipPoints, errera::vec3{ 0.749f, 0.250f, 0.749f });
        errera::vec2 position = player->transform.position + errera::random::onUnitCircle() * errera::random::getReal(200.0f, 500.0f);
        errera::Transform transform{ position, errera::random::getReal(0.0f, 360.0f), 2.5};
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
        enemy->damping = 1.5f;
        enemy->fireTime = 3;
        enemy->fireTimer = 5;
        enemy->speed = (float)(errera::random::getReal() * 200) + 300.0f;
        enemy->tag = "enemy";
        _scene->AddActor(std::move(enemy));

    }
}
