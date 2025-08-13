#include "SpaceGame.h"

#include "Enemy.h"
#include "Player.h"
#include "ringBlast.h"

bool SpaceGame::Initialize() {
    _scene = std::make_unique<errera::Scene>(this);

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
        errera::vec2 position = player->transform.position + errera::random::onUnitCircle() * errera::random::getReal(200.0f, 500.0f);
        errera::Transform transform{ position, errera::random::getReal(0.0f, 360.0f), 1.25f };
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform);
        enemy->fireTime = 3;
        enemy->fireTimer = 5;
        enemy->speed = (float)(errera::random::getReal() * 200) + 300.0f;
        enemy->tag = "enemy";

        // Components
        auto spriteRenderer = std::make_unique<errera::SpriteRenderer>();
        spriteRenderer->textureName = "textures/Seraph.png";

        enemy->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<errera::RigidBody>();
        rb->damping = 1.5f;
        enemy->AddComponent(std::move(rb));

        auto collider = std::make_unique<errera::CircleCollider2D>();
        collider->radius = 60;
        enemy->AddComponent(std::move(collider));

        _scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::SpawnPlayer() {
    // Create Player
    errera::Transform transform{ errera::vec2{ errera::GetEngine().GetRenderer().GetWidth() * 0.5f , errera::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 2.5f };
    auto player = std::make_unique<Player>(transform);
    player->speed = 1000.0f;
    player->rotationRate = 280.0f;
    player->name = "player";
    player->tag = "player";

    // Components
    auto spriteRenderer = std::make_unique<errera::SpriteRenderer>();
    spriteRenderer->textureName = "textures/longsword.png";

    player->AddComponent(std::move(spriteRenderer));

    auto rb = std::make_unique<errera::RigidBody>();
    rb->damping = 0.75f;
    player->AddComponent(std::move(rb));

    auto collider = std::make_unique<errera::CircleCollider2D>();
    collider->radius = 60;
    player->AddComponent(std::move(collider));

    _scene->AddActor(std::move(player));
}

void SpaceGame::SpawnRing() {
    Player* player = _scene->GetActorByName<Player>("player");
    if (player) {
        auto sound = errera::Resources().Get<errera::AudioClip>("audio/seismic_charges.wav", errera::GetEngine().GetAudio()).get();
        if (sound) {
            errera::GetEngine().GetAudio().PlaySound(*sound);
        }

        errera::vec2 position = player->transform.position + errera::random::onUnitCircle();
        errera::Transform transform{ position, 0, .05f };
        std::unique_ptr<ringBlast> ring = std::make_unique<ringBlast>(transform);
        ring->speed = 0.5f;
        ring->tag = "player";
        ring->lifespan = 3.0f;

        // Components
        auto spriteRenderer = std::make_unique<errera::SpriteRenderer>();
        spriteRenderer->textureName = "textures/ring.png";

        ring->AddComponent(std::move(spriteRenderer));

        auto collider = std::make_unique<errera::CircleCollider2D>();
        collider->radius = 9000;
        ring->AddComponent(std::move(collider));

        _scene->AddActor(std::move(ring));
        _ring -= 1;
    }
};