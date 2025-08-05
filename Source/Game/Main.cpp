#include "Audio/AudioSystem.h"
#include "Core/File.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Game/Player.h"
#include "Game/SpaceGame.h"
#include "Input/InputSystem.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Resources/ResourceManager.h"
#include "Engine.h"

#include <iostream>
#include <vector>
#include <memory>


int main(int argc, char* argv[]) {
    errera::file::SetCurrentDirectory("Assets");

    // Initialize Engine Systems
    errera::GetEngine().Initialize();

    /*std::shared_ptr<errera::Texture> texture = std::make_shared<errera::Texture>();
    texture->Load("Ghost Front.png", errera::GetEngine().GetRenderer());*/
    auto texture = errera::ResourceManager::Instance().Get<errera::Texture>("Ghost Front.png", errera::GetEngine().GetRenderer());

    //Creates audio in the game
    errera::GetEngine().GetAudio().AddSound("unsc-engine.wav", "unsc-engine");
    errera::GetEngine().GetAudio().AddSound("unsc-fire.wav", "unsc-fire");
    errera::GetEngine().GetAudio().AddSound("cov-engine.wav", "cov-engine");
    errera::GetEngine().GetAudio().AddSound("cov-fire.wav", "cov-fire");
    errera::GetEngine().GetAudio().AddSound("explosion.wav", "kahboom");
    errera::GetEngine().GetAudio().AddSound("seismic_charges.wav", "ring-blast");

    // Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // Update Engine Systems
        errera::GetEngine().Update();
        game->Update(errera::GetEngine().GetTime().GetDeltaTime());
        
        if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Draw
        errera::vec3 color{ 0, 0, 0 };

        errera::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        errera::GetEngine().GetRenderer().Clear(); // Clear the screen with black

        errera::GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30);

        game->Draw(errera::GetEngine().GetRenderer());

        errera::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    errera::GetEngine().Shutdown();

    return 0;
}