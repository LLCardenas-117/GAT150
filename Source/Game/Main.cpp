#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) {
    //errera::Logger::SetEnabledLevels(errera::LogLevel::Error | errera::LogLevel::Debug);

    errera::file::SetCurrentDirectory("Assets");

    // Command-line arguments
    std::cout << argc << std::endl;

    for (int i = 0; i < argc; i++) {
        // c - string, read characters until 0 '\0'
        errera::Logger::Debug("Arg {}: {}", i, argv[i]);
    }

    // Streams
    // Console Streams
    //std::cout << "Hello, World!" << " The journey countinues! BUM BUM BUMMMMM!" << std::endl;
    //
    //int age{ 0 };
    //std::cout << "Enter age: ";
    //if (!(std::cin >> age)) {
    //    std::cout << "Invalid intput\n";
    //}
    //else {
    //    std::cout << "You are " << (age * 365) << " days old.\n";
    //}
    
    // File Streams
    std::fstream stream("test.txt");
    if (!stream) {
        std::cout << "Could not open file.\n";
    }
    else {
        //std::cout << stream.rdbuf();
        std::string line;

        while (std::getline(stream, line)) {
            std::cout << line << std::endl;
        }
    }

    // basic / build-in
    // int, float, double, bool, short, long

    // User Data Type Streams
    // vec2, vec3, texture
    errera::vec2 v{ 34.5f, 65.5f };
    std::cout << v << std::endl;

    errera::vec3 b{ 34.5f, 65.5f, 75.6f };
    std::cout << b << std::endl;

    std::string vstr2("{ 23.5, 24.8}");
    std::stringstream stream2(vstr2);

    std::string vstr3("{ 23.5, 24.8, 27.9}");
    std::stringstream stream3(vstr3);

    errera::vec2 v2;
    stream2 >> v2;

    std::cout << v2 << std::endl;

    errera::vec3 v3;
    stream3 >> v3;

    std::cout << v3 << std::endl;

    return 0;
    
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