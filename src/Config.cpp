#include "Config.hpp"

#include <raylib.h>

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Default values
bool D_IS_BOT_ACTIVE = true;
bool D_BOT_START_FIRST = false;
int D_BOT_MODE = 1; // 0 always make best move | 1 sometimes make the best move | 2 always make a random move

// Appearance settings
int D_BOARD_MODE = 0; // 0 default classic board | 1 full board
Color D_BACKGROUND_COLOR = {0, 0, 0, 255};
Color D_LINE_COLOR = {255, 255, 255, 255};
float D_LINE_WIDTH = 2.0f;
float D_FINISH_LINE_WIDTH = 2.5f;
Color D_TEXT_COLOR = {255, 255, 255, 255};

json D_SETTINGS = {
    {"isBotActive", D_IS_BOT_ACTIVE},
    {"botStartFirst", D_BOT_START_FIRST},
    {"botMode", D_BOT_MODE},

    {"backgroundColor", {D_BACKGROUND_COLOR.r, D_BACKGROUND_COLOR.g, D_BACKGROUND_COLOR.b, D_BACKGROUND_COLOR.a}},
    {"lineColor", {D_LINE_COLOR.r, D_LINE_COLOR.g, D_LINE_COLOR.b, D_LINE_COLOR.a}},
    {"boardMode", D_BOARD_MODE},
    {"lineWidth", D_LINE_WIDTH},
    {"finishLineWidth", D_FINISH_LINE_WIDTH},
    {"textColor", {D_TEXT_COLOR.r, D_TEXT_COLOR.g, D_TEXT_COLOR.b, D_TEXT_COLOR.a}},

};

void LoadDefaults()
{
    D_IS_BOT_ACTIVE = D_SETTINGS["isBotActive"];
    D_BOT_START_FIRST = D_SETTINGS["botStartFirst"];
    D_BOT_MODE = D_SETTINGS["botMode"];

    D_BACKGROUND_COLOR = Color(D_SETTINGS["backgroundColor"][0], D_SETTINGS["backgroundColor"][1], D_SETTINGS["backgroundColor"][2], D_SETTINGS["backgroundColor"][3]);
    D_LINE_COLOR = Color(D_SETTINGS["lineColor"][0], D_SETTINGS["lineColor"][1], D_SETTINGS["lineColor"][2], D_SETTINGS["lineColor"][3]);
    D_BOARD_MODE = D_SETTINGS["boardMode"];
    D_LINE_WIDTH = D_SETTINGS["lineWidth"];
    D_FINISH_LINE_WIDTH = D_SETTINGS["finishLineWidth"];
    D_TEXT_COLOR = Color(D_SETTINGS["textColor"][0], D_SETTINGS["textColor"][1], D_SETTINGS["textColor"][2], D_SETTINGS["textColor"][3]);
}

void Load()
{
    std::ifstream file(DEFAULT_CONFIG_PATH);

    json loadedSettings;

    try
    {
        loadedSettings = json::parse(file);

        file.close();
    }
    catch (const json::parse_error &e)
    {
        std::cout << e.what() << std::endl;

        LoadDefaults();

        return;
    }

    try
    {
        D_IS_BOT_ACTIVE = loadedSettings["isBotActive"];
        D_BOT_START_FIRST = loadedSettings["botStartFirst"];
        D_BOT_MODE = loadedSettings["botMode"];

        D_BACKGROUND_COLOR = Color(loadedSettings["backgroundColor"][0], loadedSettings["backgroundColor"][1], loadedSettings["backgroundColor"][2], loadedSettings["backgroundColor"][3]);
        D_LINE_COLOR = Color(loadedSettings["lineColor"][0], loadedSettings["lineColor"][1], loadedSettings["lineColor"][2], loadedSettings["lineColor"][3]);
        D_BOARD_MODE = loadedSettings["boardMode"];
        D_LINE_WIDTH = loadedSettings["lineWidth"];
        D_FINISH_LINE_WIDTH = loadedSettings["finishLineWidth"];
        D_TEXT_COLOR = Color(loadedSettings["textColor"][0], loadedSettings["textColor"][1], loadedSettings["textColor"][2], loadedSettings["textColor"][3]);
    }
    catch (const json::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Save()
{
    LoadDefaults();

    std::ofstream file(DEFAULT_CONFIG_PATH);

    file << D_SETTINGS.dump() << std::endl;

    file.close();
}