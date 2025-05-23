#include "Engine.hpp"

#include <tuple>
#include <optional>
#include <vector>
#include <stdlib.h>

bool CheckWinForPlayer(CellType (&board)[9], CellType player, const int (&winCombos)[8][3])
{
    for (const auto combo : winCombos)
    {
        int a = combo[0];
        int b = combo[1];
        int c = combo[2];

        if (board[a] == player && board[a] == board[b] && board[b] == board[c])
        {
            return true;
        }
    }

    return false;
}

std::tuple<int, std::optional<int>> MiniMax(CellType (&board)[9], bool isXTurn, const int (&winCombos)[8][3], int depth = 0)
{
    if (CheckWinForPlayer(board, CellType::X, winCombos))
    {
        return std::make_tuple(10 - depth, std::nullopt);
    }
    if (CheckWinForPlayer(board, CellType::O, winCombos))
    {
        return std::make_tuple(depth - 10, std::nullopt);
    }

    bool hasEmpty = false;
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] == CellType::EMPTY)
        {
            hasEmpty = true;
            break;
        }
    }

    if (!hasEmpty)
    {
        return std::make_tuple(0, std::nullopt); // Draw
    }

    int bestScore = isXTurn ? -9999 : 9999;
    std::optional<int> bestMove = std::nullopt;

    for (int i = 0; i < 9; i++)
    {
        if (board[i] == CellType::EMPTY)
        {
            board[i] = isXTurn ? CellType::X : CellType::O;

            int score = std::get<0>(MiniMax(board, !isXTurn, winCombos, depth + 1));

            board[i] = CellType::EMPTY;

            if (isXTurn)
            {
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = i;
                }
            }
            else
            {
                if (score < bestScore)
                {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }
    }

    return std::make_tuple(bestScore, bestMove);
}

void MakeBestMove(CellType (&board)[9], bool isXTurn, const int (&winCombos)[8][3])
{
    const auto &[score, move] = MiniMax(board, isXTurn, winCombos);

    if (move.has_value())
    {
        board[move.value()] = CellType::O;
    }
}

void MakeRandMove(CellType (&board)[9])
{
    std::vector<int> emptyCellsIndexes = {};

    for (int i = 0; i < 9; i++)
    {
        if (board[i] == CellType::EMPTY)
        {
            emptyCellsIndexes.push_back(i);
        }
    }

    if (emptyCellsIndexes.size() > 0)
    {
        int rIndex = rand() % emptyCellsIndexes.size();
        int rMove = emptyCellsIndexes[rIndex];

        board[rMove] = CellType::O;
    }
}

void SometimesMakeBestMove(CellType (&board)[9], bool isXTurn, const int (&winCombos)[8][3])
{
    bool choice = (rand() % 2 == 0);

    if (choice)
    {
        MakeRandMove(board);
    }
    else
    {
        MakeBestMove(board, isXTurn, winCombos);
    }
}

void MakeMove(int mode, CellType (&board)[9], bool isXTurn, const int (&winCombos)[8][3])
{
    switch (mode)
    {
    case 0:
        MakeBestMove(board, isXTurn, winCombos);
        break;
    case 1:
        SometimesMakeBestMove(board, isXTurn, winCombos);
        break;
    default:
        MakeRandMove(board);
        break;
    }
}