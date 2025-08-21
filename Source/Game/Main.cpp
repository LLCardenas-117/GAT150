#include "Game/SpaceGame.h"

class A {
public:
    A() = default;
    A(int size) : size{ size } 
    {
        buffer = new int[size];
        for (int i = 0; i < size; i++) buffer[i] = i;
    }
    A(const A& other) :
        size{ other.size }
    {
        buffer = new int[other.size];
        for (int i = 0; i < size; i++) buffer[i] = i;
    }
    A& operator = (const A& other) {
        size = other.size * 2;
        buffer = other.buffer;
        return *this;
    }
    ~A() = default;

public:
    int size{ 0 };
    int* buffer{ nullptr };
};

int main(int argc, char* argv[]) {
    //errera::Logger::SetEnabledLevels(errera::LogLevel::Error | errera::LogLevel::Debug);

    //A a1{ 4 };
    //std::cout << a1.size << std::endl;
    //std::cout << a1.buffer[2] << std::endl;

    //A a2{a1}; // copy constructor

    //a1.buffer[2] = 45;

    //std::cout << a2.size << std::endl;
    //std::cout << a2.buffer[2] << std::endl;


    //A a3;
    //a3 = a1; // assignment operator

    //std::cout << a3.size << std::endl;

    //return 0;

    errera::file::SetCurrentDirectory("Assets");
    
    // Initialize Engine Systems
    errera::GetEngine().Initialize();
    errera::Logger::Info("Initializing Engine");

    errera::Logger::Warning("Need to fix transparent pixels!");

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