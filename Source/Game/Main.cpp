#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"

int main(int argc, char* argv[]) {
    errera::file::SetCurrentDirectory("Assets/Platformer");
    errera::Logger::Info("Current directory {}", errera::file::GetCurrentDirectory());
    
    // Initialize Engine Systems
    errera::GetEngine().Initialize();
    errera::Logger::Info("Initializing Engine");

    // Initialize Game
    //std::unique_ptr<errera::Game> game = std::make_unique<SpaceGame>();
    std::unique_ptr<errera::Game> game = std::make_unique<PlatformerGame>();
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