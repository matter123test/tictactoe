#include "Window.hpp"
#include "Common.hpp"
#include "Config.hpp"

#include <raylib.h>
#include <rlgl.h>
#include <cmath>

const int GRID_SIZE = 3;
const int GRID_CELL_SIZE = CELL_SIZE * GRID_SIZE;
const int CELL_SIZE = 60;
const int BOARD_OFFSET_X = WINDOW_WIDTH / 2 - CELL_SIZE * 3 / 2;
const int BOARD_OFFSET_Y = WINDOW_HEIGHT / 2 - CELL_SIZE * 3 / 2;

const float X_OFFSET = 10.0f;
const float O_OFFSET = 10.0f;

const int FINISH_LINE_OFFSET = 50;

const char *GetStrFromCellId(CellType type)
{
    switch (type)
    {
    case CellType::EMPTY:
        return "Empty";
    case CellType::X:
        return "Player X";
    case CellType::O:
        return "Player O";
    default:
        return "UNKNOWN";
    }
}

int GetIndex(int i, int j) { return j * GRID_SIZE + i; }

Vector2 Vec2Lerp(const Vector2 &a, const Vector2 &b, float t) { return {std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t)}; }

void DrawX(const float x, const float y)
{
    DrawLineEx({x + X_OFFSET, y + X_OFFSET}, {x + CELL_SIZE - X_OFFSET, y + CELL_SIZE - X_OFFSET}, D_LINE_WIDTH, D_LINE_COLOR);
    DrawLineEx({x + CELL_SIZE - X_OFFSET, y + X_OFFSET}, {x + X_OFFSET, y + CELL_SIZE - X_OFFSET}, D_LINE_WIDTH, D_LINE_COLOR);
}

void DrawO(const float x, const float y)
{
    rlSetLineWidth(D_LINE_WIDTH);
    DrawCircleLinesV({x + CELL_SIZE / 2, y + CELL_SIZE / 2}, CELL_SIZE / 2 - O_OFFSET, D_LINE_COLOR);
}

void DrawBoard(const float x, const float y, CellType (&board)[])
{
    for (int i = 0; i <= GRID_SIZE; ++i)
    {
        if (D_BOARD_MODE == 0 && i == 0 | i == 3)
        {
            continue;
        }

        DrawLineEx({x, y + CELL_SIZE * i}, {x + GRID_CELL_SIZE, y + CELL_SIZE * i}, D_LINE_WIDTH, D_LINE_COLOR); // Horizontal
        DrawLineEx({x + CELL_SIZE * i, y}, {x + CELL_SIZE * i, y + GRID_CELL_SIZE}, D_LINE_WIDTH, D_LINE_COLOR); // Vertical
    }

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            CellType cell = board[GetIndex(i, j)];

            switch (cell)
            {
            case CellType::X:
                DrawX(i * CELL_SIZE + BOARD_OFFSET_X, j * CELL_SIZE + BOARD_OFFSET_Y);
                break;
            case CellType::O:
                DrawO(i * CELL_SIZE + BOARD_OFFSET_X, j * CELL_SIZE + BOARD_OFFSET_Y);
                break;
            default:
                break;
            }
        }
    }
}

int GetGridIFromMouse() { return (GetMouseX() - BOARD_OFFSET_X) / CELL_SIZE; }
int GetGridJFromMouse() { return (GetMouseY() - BOARD_OFFSET_X) / CELL_SIZE; };

void DrawFinishLine(const int a, const int c, bool reset)
{
    static Vector2 aPos;
    static Vector2 cPos;
    static Vector2 lPos = aPos;

    if (reset)
    {
        aPos = {-15, -15};
        cPos = {-15, -15};
        lPos = aPos;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (GetIndex(i, j) == a)
            {
                aPos = {static_cast<float>(i) * CELL_SIZE + BOARD_OFFSET_X + CELL_SIZE / 2,
                        static_cast<float>(j) * CELL_SIZE + BOARD_OFFSET_Y + CELL_SIZE / 2};
            }
            else if (GetIndex(i, j) == c)
            {
                cPos = {static_cast<float>(i) * CELL_SIZE + BOARD_OFFSET_X + CELL_SIZE / 2,
                        static_cast<float>(j) * CELL_SIZE + BOARD_OFFSET_Y + CELL_SIZE / 2};
            }
        }
    }

    // Adjust the length of the finish line based on the direction
    if (aPos.x == cPos.x) // Vertical line
    {
        aPos.y -= FINISH_LINE_OFFSET;
        cPos.y += FINISH_LINE_OFFSET;
    }
    else if (aPos.y == cPos.y) // Horizontal line
    {
        aPos.x -= FINISH_LINE_OFFSET;
        cPos.x += FINISH_LINE_OFFSET;
    }
    else if ((cPos.x - aPos.x) == (cPos.y - aPos.y)) // Diagonal top-left to bottom-right
    {
        aPos.x -= FINISH_LINE_OFFSET;
        aPos.y -= FINISH_LINE_OFFSET;
        cPos.x += FINISH_LINE_OFFSET;
        cPos.y += FINISH_LINE_OFFSET;
    }
    else if ((cPos.x - aPos.x) == -(cPos.y - aPos.y)) // Diagonal top-right to bottom-left
    {
        aPos.x -= FINISH_LINE_OFFSET;
        aPos.y += FINISH_LINE_OFFSET;
        cPos.x += FINISH_LINE_OFFSET;
        cPos.y -= FINISH_LINE_OFFSET;
    }

    // Interpolate the line position
    if (!(lPos.x == cPos.x && lPos.y == cPos.y))
    {
        lPos = Vec2Lerp(lPos, cPos, 0.5f);
    }

    // Draw the finish line
    DrawLineEx(aPos, lPos, D_FINISH_LINE_WIDTH, D_LINE_COLOR);
}