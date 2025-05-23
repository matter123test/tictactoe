#include "Window.hpp"
#include "Game.hpp"

#include <raylib.h>

// Initialize window
void Window::Init()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_TRANSPARENT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    SetTargetFPS(60);

    Game::Init();
}

void Window::Update()
{
    Game::Update();
}

void Window::Draw()
{
    Game::Draw();
}

void Window::Close()
{
    CloseWindow();
}

void Window::Run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

        Update();
        Draw();

        EndDrawing();
    }
}