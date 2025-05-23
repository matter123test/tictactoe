#include "Game.hpp"
#include "Common.hpp"
#include "Engine.hpp"
#include "Config.hpp"

#include <raylib.h>
#include <iostream>
#include <filesystem>

CellType board[9] = {};
const int winCombos[8][3] = {
    {0, 1, 2}, // Horizontally
    {3, 4, 5},
    {6, 7, 8},

    {0, 3, 6}, // Vertically
    {1, 4, 7},
    {2, 5, 8},

    {0, 4, 8}, // Diagonally
    {6, 4, 2}

};

enum class GameState
{
    DRAW = 0,
    END = 1,
    CONTINUE = 2
};

GameState GetGameState();

// On game over
bool canDrawEndText = false;
std::string endText = "";
void UpdateEndText(const std::string text) { endText = text; }

bool isXTurn;
bool botCanMove;

void Game::Init()
{
    if (std::filesystem::exists(DEFAULT_CONFIG_PATH))
    {
        Load();
    }
    else
    {
        Save();
    }

    isXTurn = !D_BOT_START_FIRST;
    botCanMove = D_BOT_START_FIRST;
}

void Game::Update()
{
    GameState state = GetGameState();

    if (state == GameState::END)
    {
        canDrawEndText = true;
    }
    else if (state == GameState::DRAW)
    {
        canDrawEndText = true;
    }
    else if (state == GameState::CONTINUE && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        canDrawEndText = false;

        // i = column j = row
        int gridI = GetGridIFromMouse();
        int gridJ = GetGridJFromMouse();

        if (gridI >= CELL_SIZE || gridI < 0 || gridJ >= CELL_SIZE || gridJ < 0)
        {
            return;
        }

        if (board[GetIndex(gridI, gridJ)] != CellType::EMPTY)
        {
            return;
        }

        if (isXTurn && D_IS_BOT_ACTIVE)
        {
            board[GetIndex(gridI, gridJ)] = CellType::X;
            isXTurn = false;
            botCanMove = true;
        }
        else
        {
            board[GetIndex(gridI, gridJ)] = (isXTurn) ? CellType::X : CellType::O;
            isXTurn = !isXTurn;
        }
    }

    if (botCanMove && D_IS_BOT_ACTIVE)
    {
        MakeMove(D_BOT_MODE, board, isXTurn, winCombos);

        isXTurn = true;
        botCanMove = false;
    }

    if (IsKeyDown(KEY_R))
    {
        // Reset board
        for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++)
        {
            board[i] = CellType::EMPTY;
        }

        DrawFinishLine(-15, -15, true);

        UpdateEndText("");

        botCanMove = D_BOT_START_FIRST;
    }
}

void Game::Draw()
{
    ClearBackground(D_BACKGROUND_COLOR);

    DrawBoard(BOARD_OFFSET_X, BOARD_OFFSET_Y, board);

    if (canDrawEndText)
    {
        DrawText(endText.c_str(), 0, 0, 15, D_TEXT_COLOR);
    }
}

GameState GetGameState()
{
    for (const auto combo : winCombos)
    {
        int a = combo[0];
        int b = combo[1];
        int c = combo[2];

        if (board[a] != CellType::EMPTY && board[a] == board[b] && board[b] == board[c])
        {
            UpdateEndText(GetStrFromCellId(board[a]) + std::string(" Won!"));

            DrawFinishLine(a, c, false);

            return GameState::END;
        }
    }

    bool hasEmpty = false;

    for (const auto &cell : board)
    {
        if (cell == CellType::EMPTY)
        {
            hasEmpty = true;
            break;
        }
    }

    if (!hasEmpty)
    {
        UpdateEndText("Draw!");

        return GameState::DRAW;
    }

    return GameState::CONTINUE;
}