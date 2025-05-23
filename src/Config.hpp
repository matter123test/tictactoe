#pragma once

#include <raylib.h>

#define DEFAULT_CONFIG_PATH "options.json"

extern bool D_IS_BOT_ACTIVE;
extern bool D_BOT_START_FIRST;
extern Color D_BACKGROUND_COLOR;
extern Color D_LINE_COLOR;
extern int D_BOARD_MODE;
extern float D_LINE_WIDTH;
extern float D_FINISH_LINE_WIDTH;
extern Color D_TEXT_COLOR;
extern int D_BOT_MODE;

void Load();
void Save();