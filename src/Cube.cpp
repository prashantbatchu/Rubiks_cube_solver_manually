#include "Cube.hpp"
#include "Utils.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;


void rotate_face_cw(vector<vector<char>> &face){
    vector<vector<char>>T=face;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            face[j][2-i] = T[i][j];
        }
    }
}

void rotator_x(vector<char> &temp,int e1,int e2,int e3,int e4,int idx,vector<vector<char>> faces[6]){
    for(int i=0;i<3;i++) faces[e1][idx][i] = faces[e2][idx][i];
    for(int i=0;i<3;i++) faces[e2][idx][i] = faces[e3][idx][i];
    for(int i=0;i<3;i++) faces[e3][idx][i] = faces[e4][idx][i];
    for(int i=0;i<3;i++) faces[e4][idx][i] = temp[i];

}



Cube::Cube(){
    for(int i=0;i<6;i++){
        faces[i] = vector<vector<char>>(3, vector<char>(3, ' '));
    }
}
void Cube::display(){
    for(int i=0;i<3;i++){
        cout<< "      ";
        for(int j=0;j<3;j++) cout << getColor(faces[2][i][j]);
        cout<< endl;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)cout << getColor(faces[4][i][j]);
        for(int j=0;j<3;j++)cout << getColor(faces[0][i][j]);
        for(int j=0;j<3;j++) cout << getColor(faces[5][i][j]);
        for(int j=0;j<3;j++)cout << getColor(faces[1][i][j]);
        cout << endl;
    }
    for(int i=0;i<3;i++){
        cout<< "      ";
        for(int j=0;j<3;j++)cout<<getColor(faces[3][i][j]);
        cout<< endl;
    }
    cout<<endl;
}

void Cube::move_R(){
    // Rotate the right face clockwise
    vector<char>temp={faces[2][0][2], faces[2][1][2], faces[2][2][2]};
    // rotator_y(temp,2,0,3,1,2,faces);
    for(int i=0;i<3;i++) faces[2][i][2] = faces[0][i][2];
    for(int i=0;i<3;i++) faces[0][i][2] = faces[3][i][2];
    for(int i=0;i<3;i++) faces[3][i][2] = faces[1][2-i][0];
    for(int i=0;i<3;i++) faces[1][2-i][0] = temp[i];
    rotate_face_cw(faces[5]);
}

void Cube::move_L(){
    // Rotate the left face clockwise
    vector<char>temp={faces[2][0][0], faces[2][1][0], faces[2][2][0]};
    for(int i=0;i<3;i++) faces[2][i][0] = faces[1][2-i][2];
    for(int i=0;i<3;i++) faces[1][i][2] = faces[3][2-i][0];
    for(int i=0;i<3;i++) faces[3][i][0] = faces[0][i][0];
    for(int i=0;i<3;i++) faces[0][i][0] = temp[i];
    
    rotate_face_cw(faces[4]);
}


void Cube::move_U(){
    // Rotate the upper face clockwise
    vector<char>temp={faces[0][0][0], faces[0][0][1], faces[0][0][2]};
    rotator_x(temp,0,5,1,4,0,faces);
    rotate_face_cw(faces[2]);
}
void Cube::move_D(){
    // Rotate the down face clockwise
    vector<char>temp={faces[0][2][0], faces[0][2][1], faces[0][2][2]};
    rotator_x(temp,0,4,1,5,2,faces);
    rotate_face_cw(faces[3]);
}
void Cube::move_F(){
    // rotate the front face clockwise
    vector<char> temp = { faces[2][2][0], faces[2][2][1], faces[2][2][2] };

    faces[2][2][0] = faces[4][2][2];
    faces[2][2][1] = faces[4][1][2];
    faces[2][2][2] = faces[4][0][2];

    faces[4][0][2] = faces[3][0][0];
    faces[4][1][2] = faces[3][0][1];
    faces[4][2][2] = faces[3][0][2];

    faces[3][0][0] = faces[5][2][0];
    faces[3][0][1] = faces[5][1][0];
    faces[3][0][2] = faces[5][0][0];

    faces[5][0][0] = temp[0];
    faces[5][1][0] = temp[1];
    faces[5][2][0] = temp[2];

    rotate_face_cw(faces[0]);
}
void Cube::move_B(){
    // rotate the back face clockwise
    vector<char> temp = { faces[2][0][0], faces[2][0][1], faces[2][0][2] };

    faces[2][0][0] = faces[5][0][2];
    faces[2][0][1] = faces[5][1][2];
    faces[2][0][2] = faces[5][2][2];

    faces[5][0][2] = faces[3][2][2];
    faces[5][1][2] = faces[3][2][1];
    faces[5][2][2] = faces[3][2][0];

    faces[3][2][0] = faces[4][0][0];
    faces[3][2][1] = faces[4][1][0];
    faces[3][2][2] = faces[4][2][0];

    faces[4][0][0] = temp[2];
    faces[4][1][0] = temp[1];
    faces[4][2][0] = temp[0];

    rotate_face_cw(faces[1]);
}


void Cube::move_Ri(){
    // Rotate the right face counter-clockwise
    move_R(); move_R(); move_R();
}

void Cube::move_Li(){
    // Rotate the left face counter-clockwise1
    move_L(); move_L(); move_L();
}

void Cube::move_Ui(){
    // Rotate the upper face counter-clockwise
    move_U(); move_U(); move_U();
}

void Cube::move_Di(){
    // Rotate the down face counter-clockwise
    move_D(); move_D(); move_D();
}

void Cube::move_Fi(){
    // Rotate the front face counter-clockwise
    move_F(); move_F(); move_F();
}

void Cube::move_Bi(){
    // Rotate the back face counter-clockwise
    move_B(); move_B(); move_B();
}


void Cube::applymove(string move){
    if(move=="R") move_R();
    else if(move=="L") move_L();
    else if(move=="U") move_U();
    else if(move=="D") move_D();
    else if(move=="F") move_F();
    else if(move=="B") move_B();
    else if(move=="R'") move_Ri();
    else if(move=="L'") move_Li();
    else if(move=="U'") move_Ui();
    else if(move=="D'") move_Di();
    else if(move=="F'") move_Fi();
    else if(move=="B'") move_Bi();
    else if(move=="R2"){ move_R(); move_R(); }
    else if(move=="L2"){ move_L(); move_L(); }
    else if(move=="U2"){ move_U(); move_U(); }
    else if(move=="D2"){ move_D(); move_D(); }
    else if(move=="F2"){ move_F(); move_F(); }
    else if(move=="B2"){ move_B(); move_B(); }
}

void Cube::shufflecube_random(int moves){
    vector<string> mooves={"R","L","U","D","F","B","R'","L'","U'","D'","F'","B'","R2","L2","U2","D2","F2","B2"};
    
    for(int i=0;i<moves;i++){
        int idx = rand() % mooves.size();
        cout<< mooves[idx] << " ";
        applymove(mooves[idx]);
    }
    cout<<endl;
}

