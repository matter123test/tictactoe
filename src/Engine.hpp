#pragma once

#include "Common.hpp"
#include <tuple>
#include <optional>

void MakeMove(int mode, CellType (&board)[9], bool isXTurn, const int (&winCombos)[8][3]);