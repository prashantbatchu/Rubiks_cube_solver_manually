#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include <string>
#include "Cube.hpp"

std::vector<std::string> solve_white_cross(Cube &cube);
std::vector<std::string> solve_white_corners(Cube &cube);
std::vector<std::string> solve_middle_layer(Cube &cube);
std::vector<std::string> solve_yellow_cross(Cube &cube);
std::vector<std::string> solve_yellow_corners(Cube &cube);

void solver(Cube &cube);

#endif
