#!/bin/bash

# Compilation
meson setup build
meson compile -C build

# Run
cd build
./tictactoe