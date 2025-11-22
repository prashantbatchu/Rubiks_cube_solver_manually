// #ifndef CUBE_HPP
// #define CUBE_HPP
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <queue>
#include <set>
#include <cstdlib>
using namespace std;


class Cube{
    public:
        vector<vector<char>> faces[6];   
        Cube();
        void display();

        void shufflecube_random(int moves);
        void applymove(string move);

        void move_R();  
        void move_L();  
        void move_U();  
        void move_D();
        void move_F();
        void move_B();
        void move_Ri();  
        void move_Li(); 
        void move_Ui();
        void move_Di();
        void move_Fi();
        void move_Bi();

};

// #endif
