#include "Utils.hpp"
#include <algorithm>
using namespace std;
#define r "\033[41m  \033[0m"
#define g "\033[42m  \033[0m"
#define b "\033[44m  \033[0m"
#define y "\033[43m  \033[0m"
#define w "\033[47m  \033[0m"
#define o "\033[48;2;255;165;0m  \033[0m"

string getColor(char c){
    switch(c){
        case 'r': case 'R': return r;
        case 'g': case 'G': return g;
        case 'b': case 'B': return b;
        case 'y': case 'Y': return y;
        case 'w': case 'W': return w;
        case 'o': case 'O': return o;
    }
    return "  ";
}

void cube_input(Cube &cube, const string &input_str){
    for(int i=0;i<6;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                cube.faces[i][j][k] = input_str[i*9 + j*3 + k];
            }
        }
    }
    
}

bool is_white_cross_solved(Cube &cube){
    if(cube.faces[0][0][1]== 'w' && cube.faces[2][2][1]=='r' &&
       cube.faces[0][1][0]=='w' && cube.faces[5][1][0]=='g' &&
       cube.faces[0][1][2]=='w' && cube.faces[3][0][1]=='o' &&
       cube.faces[0][2][1]=='w' && cube.faces[4][1][2]=='b'){
        return true;
    }
    return false;
}

int cross_score(Cube &c){
    int s=0;
    if(c.faces[0][0][1]=='w' && c.faces[2][2][1]=='r') s++; // top edge must match red center
    if(c.faces[0][1][0]=='w' && c.faces[5][1][0]=='g') s++; // left edge match green center
    if(c.faces[0][1][2]=='w' && c.faces[3][0][1]=='o') s++; // right edge match orange center
    if(c.faces[0][2][1]=='w' && c.faces[4][1][2]=='b') s++; // bottom edge match blue center
    return s;
}

string inverseMove(const string& m){
    if(m.size()==1) return m + "'";         
    if(m.size()==2 && m[1]=='\'') return string(1,m[0]); 
    return m;                                
}
char faceOf(const string& m){ return m[0]; } 




