#pragma once

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define WINDOW_TITLE "Tic Tac Toe"

class Window
{
private:
    void Init();
    void Update();
    void Draw();
    void Close();

public:
    Window()
    {
        Init();
    }

    ~Window()
    {
        Close();
    }

    void Run();
};