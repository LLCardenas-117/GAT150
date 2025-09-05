# GAT150 — C++ Game/Engine Coursework Project

> A lightweight C++ project for learning game/engine fundamentals: core loop, input, timing, rendering, assets, and object composition.

## ✨ Features (high level)
- Game loop: initialize → update → draw → shutdown
- Scene/actor model with update & render phases
- Input handling (keyboard/mouse) and timing (delta time)
- Resource management for textures/audio/etc. (as applicable)
- Simple math utilities (vectors, random, colors) for gameplay code
- Buildable via Visual Studio solution (`GAT150.sln`)

---

## 🧭 Project Layout

- **`Source/`** is where you’ll spend almost all your time. Typical subfolders:
  - `Core/` – Application/Engine, Time, Logger, File utilities
  - `Input/` – InputSystem
  - `Renderer/` – Renderer, Texture/Sprite, Color
  - `Audio/` – AudioSystem (if used)
  - `Framework/` – Actor, Component, Scene, Prefabs
  - `Math/` – Vector2, Rect, Random
  - `Game/` – Game-specific classes and the main game state

---

## 🧩 Class & System Overview

> Replace the placeholders with your actual classes. Keep the short, “what it does + how to use” format—reviewers love it.

### Core / App
- **`Engine`** 
  Owns initialization/shutdown, main loop, and system singletons (renderer, audio, input).  
  **Key methods:** `Initialize(cfg)`, `Run()`, `Shutdown()`  
  **Usage:** Create once in `main`, call `Run()` to start the game loop.

- **`Time`**  
  Computes frame delta time (`dt`) and tracks total time.  
  **Usage:** Read `Time::deltaTime` inside update; call `Time::Tick()` each frame.

- **`Logger`**  
  Lightweight logging with levels; used for diagnostics.

### Input
- **`InputSystem`**  
  Polls keyboard/mouse; exposes edge/level queries.  
  **Usage:** `input.GetKeyDown(Key::Space)`; call `Update()` every frame.

### Graphics
- **`Renderer`**  
  Initializes the window/context; clears/draws each frame; presents backbuffer.  
  **Usage:** `renderer.BeginFrame(); … draw …; renderer.EndFrame();`

- **`Texture` / `Sprite`**  
  Loads images and draws them (optionally with source rect, rotation, scale).  
  **Usage:** `sprite.Draw(renderer, position, rotation, scale);`

### Audio
- **`AudioSystem`** *(if present)*  
  Loads/plays SFX/music.  
  **Usage:** `audio.Play("laser");`

### Framework (Game Object Model)
- **`Actor`**  
  Basic entity with `position`, `rotation`, `scale`, `Update(dt)`, `Draw(renderer)`.  
  May own a list of `Component`s for behavior.

- **`Component`**  
  Plug-in behavior for Actors (e.g., `SpriteComponent`, `PhysicsComponent`, `InputComponent`).  
  **Usage:** `actor->AddComponent<MoveComponent>(speed);`

- **`Scene`**  
  Owns/updates/draws all `Actor`s; handles add/remove and lookups.  
  **Usage:** `scene.Add(std::move(actor)); scene.Update(dt); scene.Draw(renderer);`

### Math & Utilities
- **`Vector2`**  
  2D vector math (add/subtract, dot, normalize, length).  
  **Usage:** `pos += dir * speed * dt;`

- **`Random`**, **`Rect`**, **`Transform`** *(optional)*  
  Convenience helpers for gameplay and layout.

### Game Layer
- **`Game` / `GameState`**  
  Wires systems together (Engine, Scene, Input, Renderer).  
  Spawns initial actors, updates game rules, and handles win/lose conditions.

---

## 🚀 Getting Started

### Prerequisites
- **Windows + Visual Studio** (project uses a `.sln`)
- **C++17** (or higher) toolset
- Any third-party libs your project uses (e.g., **SDL2**, **GLM**, **ImGui**).  
  > TODO: Replace this line with the exact libraries you’re using (if any).

### Build & Run
1. Clone the repo:
   ```bash
   git clone https://github.com/LLCardenas-117/GAT150.git

2. Open GAT150.sln in Visual Studio.

3. Select Debug or Release, x64 (as applicable).

4. Press F5 (Run) or Ctrl+F5 (Run without debugging).

## Controls

Player 1:
  - W: Jump
  - A: Move Left
  - D: Move Right
  - E: Attack

Player 2:
  - Up Arrow: Jump
  - Left Arrow: Move Left
  - Right Arrow: Move Right
  - Page Down: Attack

## Assets

- Textures: Assets/Platformer/Textures
- Animations: Assets/Plateformer/Animations (json)
- Scenes: Assets/Plateformer/Scenes
- Tilemaps: Assets/Plateformer/Tilemaps

This project is licensed under the MIT License
