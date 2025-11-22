// #ifndef solve_HPP
// #define solve_HPP
#pragma once
#include "cube.hpp"


void solver(Cube &cube);
vector<string> solve_white_cross(Cube &cube);
vector<string> solve_white_corners(Cube &cube);
vector<string> solve_middle_layer(Cube &cube);
vector<string> solve_yellow_cross(Cube &cube);
vector<string> solve_yellow_corners(Cube &cube);

// #endif
