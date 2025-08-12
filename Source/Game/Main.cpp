#include "Game/SpaceGame.h"


int main(int argc, char* argv[]) {
    //errera::Logger::SetEnabledLevels(errera::LogLevel::Error | errera::LogLevel::Debug);

    errera::file::SetCurrentDirectory("Assets");

    // Initialize Engine Systems
    errera::GetEngine().Initialize();
    errera::Logger::Info("Initializing Engine");

    errera::Logger::Warning("Need to fix transparent pixels!");

    // Creates audio in the game
    /*errera::GetEngine().GetAudio().AddSound("audio/unsc-engine.wav", "unsc-engine");
    errera::GetEngine().GetAudio().AddSound("audio/unsc-fire.wav", "unsc-fire");
    errera::GetEngine().GetAudio().AddSound("audio/cov-engine.wav", "cov-engine");
    errera::GetEngine().GetAudio().AddSound("audio/cov-fire.wav", "cov-fire");
    errera::GetEngine().GetAudio().AddSound("audio/explosion.wav", "kahboom");
    errera::GetEngine().GetAudio().AddSound("audio/seismic_charges.wav", "ring-blast");
    errera::Logger::Info("Added audio files to Game");*/

    // Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();
    errera::Logger::Info("Initializing Game");

    SDL_Event e;
    bool quit = false;

    float rotate = 0;

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

        game->Draw(errera::GetEngine().GetRenderer());

        errera::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    errera::GetEngine().Shutdown();
    errera::Logger::Info("Shuting down Game and Engine");

    return 0;
}