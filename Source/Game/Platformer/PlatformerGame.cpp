#include "../GamePCH.h"
#include "PlatformerGame.h"

bool PlatformerGame::Initialize() {
    _scene = std::make_unique<errera::Scene>(this);
    _scene->Load("scenes/prototypes.json");
    _scene->Load("scenes/level.json");
    return false;
}

void PlatformerGame::Update(float dt) {
    switch (_gameState) {

    case GameState::Initialize:
        _gameState = GameState::StartGame;
        break;

    case GameState::Title:
        break;

    case GameState::StartGame:
        RoundAnnouncer();
        _gameState = GameState::StartLevel;
        break;

    case GameState::StartLevel:
        SpawnPlayers();
        _gameState = GameState::Game;
        break;

    case GameState::Game:
        if (round >= 3) {
            winner = (player1Score > player2Score) ? "textures/player_1_winscreen.png" : "textures/player_2_winscreen.png";
            std::cout << winner << std::endl;
            _gameState = GameState::GameOver;
        }

        if (!_scene->GetActorByName("player2")->active) {
            player1Score++;
            round++;
            _gameState = GameState::PlayerDead;
        }

        else if (!_scene->GetActorByName("player1")->active) {
            player2Score++;
            round++;
            _gameState = GameState::PlayerDead;
        }
        break;

    case GameState::PlayerDead:
        OnPlayerDeath();
        _gameState = GameState::StartGame;
        break;

    case GameState::GameOver:
        OnPlayerDeath();
        Winscreen();
        break;

    default:
        break;
    }

    _scene->Update(errera::GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Draw(class errera::Renderer& renderer) {
    _scene->Draw(renderer);

    errera::GetEngine().GetParticleSystem().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath() {
    _scene->RemoveAllActors();
}

void PlatformerGame::OnNotify(const errera::Event& event) {

}

void PlatformerGame::Shutdown() {

}


void PlatformerGame::SpawnPlayers() {
    auto player1 = errera::Instantiate("player1");
    //player->transform.position = errera::vec2{ errera::random::getReal(0.0f, 1080.0f), errera::random::getReal(0.0f, 100.0f) };
    _scene->AddActor(std::move(player1));

    auto player2 = errera::Instantiate("player2");
    _scene->AddActor(std::move(player2));
}

void PlatformerGame::Winscreen() {
    auto winscreen = errera::Instantiate("winscreen");
    if (winscreen) {
        winscreen->GetComponent<errera::SpriteRenderer>()->textureName = winner;
        _scene->AddActor(std::move(winscreen));
    }
}

void PlatformerGame::RoundAnnouncer() {
    auto roundCounter = errera::Instantiate("round");

    if (round == 2) {
        roundCounter->GetComponent<errera::SpriteRenderer>()->textureName = "textures/round_three.png";
    }

    if (round == 1) {
        roundCounter->GetComponent<errera::SpriteRenderer>()->textureName = "textures/round_two.png";
    }

    if (round == 0) {
        roundCounter->GetComponent<errera::SpriteRenderer>()->textureName = "textures/round_one.png";
    }

    _scene->AddActor(std::move(roundCounter));
}
