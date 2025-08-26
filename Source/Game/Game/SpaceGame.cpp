#include "SpaceGame.h"

#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "ringBlast.h"

bool SpaceGame::Initialize() {
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);

    _scene = std::make_unique<errera::Scene>(this);
    _scene->Load("scene.json");
    _scene->Load("prototype.json");

    _titleText = std::make_unique<errera::Text>(errera::Resources().GetWithID<errera::Font>("title_font", "arcadeclassic.ttf", 128.0f));
    _scoreText = std::make_unique<errera::Text>(errera::Resources().GetWithID<errera::Font>("ui_font", "arcadeclassic.ttf", 48.0f));
    _livesText = std::make_unique<errera::Text>(errera::Resources().GetWithID<errera::Font>("ui_font", "arcadeclassic.ttf", 48.0f));
    _ringChargeText = std::make_unique<errera::Text>(errera::Resources().GetWithID<errera::Font>("ui_font", "arcadeclassic.ttf", 48.0f));

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

        SpawnPlayer();
        
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
            SpawnRing();
        }

        break;

    case SpaceGame::GameState::PlayerDead:
        _stateTimer -= dt;
		if (_stateTimer <= 0) {
            _lives--;
            _ring = 1;
            _ringChargeTimer = 40;
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
    _scene->Draw(renderer);

    if (_gameState == GameState::Title) {
        _titleText->Create(renderer, "Halo Space", errera::vec3{ 0, 1, 0 });
        _titleText->Draw(renderer, (float)renderer.GetHeight() / 3, (float)renderer.GetWidth() / 3);
    }

    if (_gameState == GameState::GameOver) {
        _titleText->Create(renderer, "GAME OVER", errera::vec3{ 1, 0, 0 });
        _titleText->Draw(renderer, (float)renderer.GetHeight() / 3, (float)renderer.GetWidth() / 3);
    }

	_scoreText->Create(renderer, "SCORE " + std::to_string(_score), errera::vec3{1, 1, 1});
	_scoreText->Draw(renderer, 10, 10);

    _livesText->Create(renderer, "LIVES " + std::to_string(_lives), errera::vec3{1, 1, 1});
    _livesText->Draw(renderer,(float)(renderer.GetWidth() - 200), 10);

    _ringChargeText->Create(renderer, "Ring Charges " + std::to_string(_ring), errera::vec3{ 1, 1, 1 });
    _ringChargeText->Draw(renderer, 10, (float)renderer.GetHeight() - 100);

	errera::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnNotify(const errera::Event& event) {
    std::cout << event.id << std::endl;

    if (errera::equalsIqnoreCase(event.id, "player_dead")) {
        OnPlayerDeath();
    }
    else if (errera::equalsIqnoreCase(event.id, "add_points")) {
        AddPoints(std::get<int>(event.data));
    }
}

void SpaceGame::OnPlayerDeath() {
	_gameState = GameState::PlayerDead;
    _stateTimer = 2;
}

void SpaceGame::Shutdown() {
}

void SpaceGame::SpawnEnemy() {
    errera::Actor* player = _scene->GetActorByName<errera::Actor>("player");
    if (player) {
        errera::vec2 position = player->transform.position + errera::random::onUnitCircle() * errera::random::getReal(200.0f, 500.0f);
        errera::Transform transform{ position, errera::random::getReal(0.0f, 360.0f), 1.25 };

        auto enemy = errera::Instantiate("enemy", transform);
        _scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::SpawnPlayer() {
    auto player = errera::Factory::Instance().Create<errera::Actor>("player");
    _scene->AddActor(std::move(player));
}

void SpaceGame::SpawnRing() {
    errera::Actor* player = _scene->GetActorByName<errera::Actor>("player");
    if (player) {
        errera::Transform transform{ player->transform.position, 0, 0.05f };

        auto ring = errera::Instantiate("ring", transform);
        _scene->AddActor(std::move(ring));
        _ring -= 1;
    }
}