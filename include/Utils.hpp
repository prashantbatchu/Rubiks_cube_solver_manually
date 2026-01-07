#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "Cube.hpp"

std::string getColor(char c);
void cube_input(Cube &cube, const std::string &input_str);

// Solver helpers
bool is_white_cross_solved(Cube &cube);
int cross_score(Cube &cube);
std::string inverseMove(const std::string &m);
char faceOf(const std::string &m);

#endif
