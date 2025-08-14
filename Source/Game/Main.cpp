#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) {
    //errera::Logger::SetEnabledLevels(errera::LogLevel::Error | errera::LogLevel::Debug);

    errera::file::SetCurrentDirectory("Assets");

    // load the json data from a file
    std::string buffer;
    errera::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    errera::json::Load("json.txt", document);

    // read/show the data from the json file
    std::string name;
    int age;
    float speed;
    bool isAwake;
    errera::vec2 position;
    errera::vec3 color;

    // read the json data
    /*errera::json::Read(document, "name", name);
    errera::json::Read(document, "age", age);
    errera::json::Read(document, "speed", speed);
    errera::json::Read(document, "isAwake", isAwake);
    errera::json::Read(document, "position", position);
    errera::json::Read(document, "color", color);*/

    JSON_READ(document, name);
    JSON_READ(document, age);
    JSON_READ(document, speed);
    JSON_READ(document, isAwake);
    JSON_READ(document, position);
    JSON_READ(document, color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

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