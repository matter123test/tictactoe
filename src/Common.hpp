#pragma once

extern const int GRID_SIZE;
extern const int CELL_SIZE;
extern const int BOARD_OFFSET_X;
extern const int BOARD_OFFSET_Y;

enum class CellType
{
    EMPTY,
    X,
    O
};

const char *GetStrFromCellId(CellType type);
int GetIndex(int i, int j);

void DrawX(float x, float y);
void DrawO(float x, float y);
void DrawBoard(float x, float y, CellType (&board)[]);

int GetGridIFromMouse();
int GetGridJFromMouse();

void DrawFinishLine(int a, int c, bool reset=false);