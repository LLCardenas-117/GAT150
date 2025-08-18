#include "Game/SpaceGame.h"

class Animal {
public:
    virtual void Speak() = 0;
};

class Cat : public Animal {
public:
    void Speak() override { std::cout << "Meow\n"; }
};

class Dog : public Animal {
public:
    void Speak() override { std::cout << "Bork\n"; }
    void Fetch() { std::cout << "Got the ball!"; }
};

class Bird : public Animal {
public:
    void Speak() override { std::cout << "Kaww\n"; }
};

enum class AnimalType {
    Cat,
    Dog,
    Bird
};

Animal* CreateAnimal(AnimalType id) {
    Animal* animal = nullptr;

    switch (id) {
    case AnimalType::Cat:
        animal = new Cat{};
        break;

    case AnimalType::Dog:
        animal = new Dog{};
        break;

    case AnimalType::Bird:
        animal = new Bird{};
        break;

    default:
        break;
    }

    return animal;
}

int main(int argc, char* argv[]) {
    //errera::Logger::SetEnabledLevels(errera::LogLevel::Error | errera::LogLevel::Debug);

    errera::file::SetCurrentDirectory("Assets");

    auto animal = CreateAnimal(AnimalType::Cat);

    if (animal) animal->Speak();

    auto dog = dynamic_cast<Dog*>(animal);
    if (dog) {
        dog->Fetch();
    }

    //auto spriteRenderer = errera::Factory::Instance().Create("MeshRenderer");
    //spriteRenderer->name = "Steve";

    //return 0;
    
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