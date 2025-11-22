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
#include <functional> // <-- ADD THIS


// #include "cube.hpp"
// #include "solve.hpp"


using namespace std;




/*
0-white
1-yellow
2-red
3-orange
4-blue
5-green

 */
//      red 
// blue white green yellow
//      orange


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














// #include "solver.hpp"
void cube_input(Cube &cube, const string &input_str){
    for(int i=0;i<6;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                cube.faces[i][j][k] = input_str[i*9 + j*3 + k];
            }
        }
    }
    
}












bool is_white_edge(char aa, char bb){
    return (aa=='w' || bb=='w') && !(aa=='w' && bb=='w');
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


// --- helpers (put near the top once; skip if you already added earlier) ---
static inline string inverseMove(const string& m){
    if(m.size()==1) return m + "'";          // R -> R'
    if(m.size()==2 && m[1]=='\'') return string(1,m[0]); // R' -> R
    return m;                                // R2 -> R2
}
static inline char faceOf(const string& m){ return m[0]; } // 'R' from "R", "R'", "R2"

// If you don't already have it, keep this exact scoring used by your is_white_cross_solved()
static int cross_score(Cube &c){
    int s=0;
    if(c.faces[0][0][1]=='w' && c.faces[2][2][1]=='r') s++; // top edge must match red center
    if(c.faces[0][1][0]=='w' && c.faces[5][1][0]=='g') s++; // left edge match green center
    if(c.faces[0][1][2]=='w' && c.faces[3][0][1]=='o') s++; // right edge match orange center
    if(c.faces[0][2][1]=='w' && c.faces[4][1][2]=='b') s++; // bottom edge match blue center
    return s;
}
// -------------------------------------------------------------------------


// Deterministic, short-move white-cross solver using IDDFS with pruning
vector<string> solve_white_cross(Cube &cube){
    cout << "Solving white cross (optimal-ish search)..." << endl;

    // Move set (18)
    const vector<string> MOVES = {
        "U","U'","U2","D","D'","D2",
        "L","L'","L2","R","R'","R2",
        "F","F'","F2","B","B'","B2"
    };

    // Heuristic: minimum number of edges still wrong (admissible)
    auto h = [&](Cube &c)->int { return 4 - cross_score(c); };

    // Order moves by their immediate improvement to speed up search
    auto ordered_moves = [&](Cube &c, const string &last)->vector<string>{
        struct Cand{ string m; int sc; };
        vector<Cand> cand; cand.reserve(MOVES.size());
        for(const auto &m: MOVES){
            if(!last.empty()){
                if(faceOf(m)==faceOf(last)) continue;                  // avoid R then R'
                if(inverseMove(last)==m) continue;                      // avoid cancel
            }
            Cube t = c;
            t.applymove(m);
            cand.push_back({m, cross_score(t)});
        }
        sort(cand.begin(), cand.end(), [](const Cand&a, const Cand&bl){
            return a.sc > bl.sc; // try higher score first
        });
        vector<string> out; out.reserve(cand.size());
        for(auto &x: cand) out.push_back(x.m);
        return out;
    };

    std::function<bool(Cube&, int, const string&, vector<string>&)> dfs;

    dfs = [&](Cube &cur, int depth, const string &last, vector<string> &path)->bool {
        if(is_white_cross_solved(cur)) return true;
        int heur = h(cur);
        if(heur > depth) return false; 

        auto moves = ordered_moves(cur, last);
        for(const auto &m: moves){
            Cube nxt = cur;
            nxt.applymove(m);
            path.push_back(m);
            if(dfs(nxt, depth - 1, m, path)) return true;  // recursive call now valid
            path.pop_back();
        }
        return false;
    };


    vector<string> answer;
    // Start from current score; grow depth up to a safe cap (<= 16 keeps < 20 moves well)
    int startScore = cross_score(cube);
    int minDepth = max(0, 4 - startScore);
    int maxDepth = 16; // plenty for cross; usually finds < 12
    bool found = false;

    for(int depth=minDepth; depth<=maxDepth && !found; ++depth){
        vector<string> path;
        Cube start = cube;
        if(dfs(start, depth, "", path)){
            // apply the found sequence to the real cube
            for(const auto &m: path){
                cube.applymove(m);
                cout << m << " ";
            }
            cout << endl;
            answer = std::move(path);
            found = true;
            break;
        }
    }

    if(is_white_cross_solved(cube)){
        cout << " White cross solved in " << answer.size() << " moves." << endl;
    } else {
        cout << " Failed to complete within limit. Progress " << endl;
    }

    return answer;
}


vector<string> solve_white_corners(Cube &cube){
    cout << "Solving white corners (orientation + placement)..." << endl;
    vector<string> sol;
    auto add=[&](string m){ cube.applymove(m); sol.push_back(m); cout<<m<<" "; };
    auto seq=[&](vector<string> moves){ for(auto &m:moves) add(m); };

    auto isCornerWhite=[&](int z,int i,int j){ return cube.faces[0][i][j]=='w'; };

    int safety1=0;
    while(!isCornerWhite(0,0,2) && safety1<30){
        seq({"R","B","R'","B'"}); safety1++;
        if(!isCornerWhite(0,0,2) && safety1%6==0) add("B");
    }
    int safety2=0;
    while(!isCornerWhite(0,0,0) && safety2<30){
        seq({"U","B","U'","B'"}); safety2++;
        if(!isCornerWhite(0,0,0) && safety2%6==0) add("B");
    }
    int safety3=0;
    while(!isCornerWhite(0,2,0) && safety3<30){
        seq({"L","B","L'","B'"}); safety3++;
        if(!isCornerWhite(0,2,0) && safety3%6==0) add("B");
    }
    int safety4=0;
    while(!isCornerWhite(0,2,2) && safety4<30){
        seq({"D","B","D'","B'"}); safety4++;
        if(!isCornerWhite(0,2,2) && safety4%6==0) add("B");
    }

    cout << "\n Orientation complete _ aligning corners by side colors...\n";
    map<int,char> centerColor;
    for(int f=0; f<6; ++f) centerColor[f] = cube.faces[f][1][1];

    // Helper: check if all corners aligned
    auto cornersAligned=[&](){
        bool ok=true;
        if(!(cube.faces[4][0][2]==cube.faces[4][1][2] && cube.faces[2][2][0]==cube.faces[2][2][1] && cube.faces[0][0][0]==cube.faces[0][1][1])) ok=false;
        if(!(cube.faces[2][2][2]==cube.faces[2][2][1] && cube.faces[5][0][0]==cube.faces[5][1][0] && cube.faces[0][0][2]==cube.faces[0][1][1])) ok=false;
        if(!(cube.faces[4][2][2]==cube.faces[4][1][2] && cube.faces[3][0][0]==cube.faces[3][0][1] && cube.faces[0][2][0]==cube.faces[0][1][1])) ok=false;
        if(!(cube.faces[5][2][0]==cube.faces[5][1][0] && cube.faces[3][0][2]==cube.faces[3][0][1] && cube.faces[0][2][2]==cube.faces[0][1][1])) ok=false;
        return ok;
    };

    auto cornerColors=[&](int i,int j)->pair<char,char>{
        if(i==0 && j==0) return {cube.faces[4][0][2], cube.faces[2][2][0]}; // blue-red
        if(i==0 && j==2) return {cube.faces[2][2][2], cube.faces[5][0][0]}; // red-green
        if(i==2 && j==0) return {cube.faces[4][2][2], cube.faces[3][0][0]}; // blue-orange
        if(i==2 && j==2) return {cube.faces[5][2][0], cube.faces[3][0][2]}; // green-orange
        return {'x','x'};
    };

    int tries=0;
    char c1,c2;
    while(!cornersAligned() ){
        // auto c000 = cornerColors(0,0);
        // char a = c000.first;
        // char sm_b = c000.second;
            // if(cornersAligned())break;

       while(cube.faces[4][0][2]==cube.faces[4][1][2] && cube.faces[2][2][0]==cube.faces[2][2][1]){
            seq({"F"});
// /            if(cornersAligned())break;
       }
            // if(cornersAligned())break;

       
       
       if(cube.faces[4][0][0]!=cube.faces[0][1][1] && cube.faces[2][0][0]!=cube.faces[0][1][1] ){
            c1 = cube.faces[4][0][2];
            c2 = cube.faces[2][2][0];
            seq({"L'","B","L"});
       }
       while (true){
            // char c1 = cube.faces[4][0][2];
            // char c2 = cube.faces[2][2][0];
            if ((c1 == cube.faces[4][1][2] && c2 == cube.faces[2][2][1]) || (c2 == cube.faces[4][1][2] && c1 == cube.faces[2][2][1])){
                break;
            }
            if(cornersAligned())break;
            seq({"F"});
        }
       if(cube.faces[4][0][0]==cube.faces[0][1][1]){
            seq({"L'","B'","L","B"});
            c1 = cube.faces[4][0][0];
            c2 = cube.faces[1][0][2];
       }
       else if(cube.faces[2][0][0]==cube.faces[0][1][1]){
            seq({"U","B","U'","B'"});
            c1 = cube.faces[2][0][0];
            c2 = cube.faces[1][0][2];
       }
    }
    while(cube.faces[2][2][1]!=cube.faces[2][1][1])seq({"F"});

    cout << endl;
    if(cornersAligned())
        cout << "White corners oriented & correctly placed in " << sol.size() << " moves.\n";
    else
        cout << "Some corners may still be misaligned after " << sol.size() << " moves.\n";

    return sol;
}


vector<string> solve_middle_layer(Cube &cube){
    cout << "Solving middle layer..." << endl;
    vector<string> sol;
    auto add=[&](string m){ cube.applymove(m); sol.push_back(m); cout<<m<<" "; };
    auto seq=[&](vector<string> moves){ for(auto &m:moves) add(m); };

    auto middleSolved=[&](){
        bool ok=true;
        // Front (red)
        if(cube.faces[2][1][2]!=cube.faces[2][1][1] || cube.faces[5][0][1]!=cube.faces[5][1][1]) ok=false;
        if(cube.faces[2][1][0]!=cube.faces[2][1][1] || cube.faces[4][0][1]!=cube.faces[4][1][1]) ok=false;
        if(cube.faces[3][1][0]!=cube.faces[3][1][1] || cube.faces[4][2][1]!=cube.faces[4][1][1]) ok=false;
        if(cube.faces[3][1][2]!=cube.faces[3][1][1] || cube.faces[5][2][1]!=cube.faces[5][1][1]) ok=false;
        return ok;
    };

    // --- Helper: CFOP formulas ---
       auto edgehas_yellow =[&](char a,char bb){ return a=='y' || bb=='y'; };

    // --- Insert sequences for all perspectives ---
    auto insert_red_blue  =[&](){ seq({"B'","L'","B","L","B","U","B'","U'"}); };
    auto insert_red_green =[&](){ seq({"B","R","B'","R'","B'","U'","B","U"}); };
    auto insert_green_red =[&](){ seq({"B'","U'","B","U","B","R","B'","R'"}); };
    auto insert_green_orange=[&](){ seq({"B","D","B'","D'","B'","R'","B","R"}); };
    auto insert_blue_orange=[&](){ seq({"B'","R'","B","R","B","D","B'","D'"}); };
    auto insert_blue_red  =[&](){ seq({"B","U","B'","U'","B'","L'","B","L"}); };
    auto insert_orange_green=[&](){ seq({"B'","R'","B","R","B","D","B'","D'"}); };
    auto insert_orange_blue=[&](){ seq({"B","L","B'","L'","B'","D'","B","D"}); };

    auto dummy_extract=[&](){ seq({"B'","L'","B","L","B","U","B'","U'"}); }; 

    int safe=0;
    while(!middleSolved()){
        // safe++;

        // --- 1️⃣ Check edge between faces[2] (red) and top[1] ---
        char front=cube.faces[2][0][1]; // red face top edge
        char top  =cube.faces[1][0][1];
        if(!edgehas_yellow(front,top)){
            if(front=='r'){
                if(top=='b') insert_red_blue();
                else insert_red_green();
            }
            else if(front=='b'){
                add("B");
                if(top=='o') insert_blue_orange();
                else insert_blue_red();
            }
            else if(front=='g'){
                add("B'");
                if(top=='r') insert_green_red();
                else insert_green_orange();
            }
            else{
                add("B2");
                if(top=='b') insert_orange_blue();
                else insert_orange_green();
            }
        }

        front=cube.faces[5][1][2];
        top  =cube.faces[1][1][0];
        if(!edgehas_yellow(front,top)){
            // if(front==cube.faces[5][1][1] && top==cube.faces[2][1][1]) insert_green_red();
            // else if(front==cube.faces[5][1][1] && top==cube.faces[3][1][1]) insert_green_orange();
            if(front=='r'){
                add("B");
                if(top=='b') insert_red_blue();
                else insert_red_green();
            }
            else if(front=='b'){
                add("B2");
                if(top=='o') insert_blue_orange();
                else insert_blue_red();
            }
            else if(front=='g'){
                // add("B'");
                if(top=='r') insert_green_red();
                else insert_green_orange();
            }
            else{
                add("B'");
                if(top=='b') insert_orange_blue();
                else insert_orange_green();
            }
        }

        // --- 3️⃣ Check edge between faces[4] (blue) and top[1] ---
        front=cube.faces[4][1][0];
        top  =cube.faces[1][1][2];
        if(!edgehas_yellow(front,top)){
            if(front=='r'){
                add("B'");
                if(top=='b') insert_red_blue();
                else insert_red_green();
            }
            else if(front=='b'){
                // add("B");
                if(top=='o') insert_blue_orange();
                else insert_blue_red();
            }
            else if(front=='g'){
                add("B2");
                if(top=='r') insert_green_red();
                else insert_green_orange();
            }
            else{
                add("B");
                if(top=='b') insert_orange_blue();
                else insert_orange_green();
            }
        }

        // --- 4️⃣ Check edge between faces[3] (orange) and top[1] ---
        front=cube.faces[3][2][1];
        top  =cube.faces[1][2][1];
        if(!edgehas_yellow(front,top)){
            if(front=='r'){
                add("B2");
                if(top=='b') insert_red_blue();
                else insert_red_green();
            }
            else if(front=='b'){
                add("B'");
                if(top=='o') insert_blue_orange();
                else insert_blue_red();
            }
            else if(front=='g'){
                add("B");
                if(top=='r') insert_green_red();
                else insert_green_orange();
            }
            else{
                // add("B2");
                if(top=='b') insert_orange_blue();
                else insert_orange_green();
            }
        }

        if( 
                !edgehas_yellow(cube.faces[2][1][2],cube.faces[5][0][1]) && 
                !edgehas_yellow(cube.faces[2][1][0],cube.faces[4][0][1]) && 
                !edgehas_yellow(cube.faces[3][1][0],cube.faces[4][2][1]) && 
                !edgehas_yellow(cube.faces[3][1][2],cube.faces[5][2][1])){
                     if(cube.faces[2][1][0]!=cube.faces[2][1][1] || cube.faces[5][0][1]!=cube.faces[5][1][1]) insert_red_green();
            else if(cube.faces[2][1][2]!=cube.faces[2][1][1] || cube.faces[4][0][1]!=cube.faces[4][1][1]) insert_red_blue();
            else if(cube.faces[3][1][0]!=cube.faces[3][1][1] || cube.faces[4][2][1]!=cube.faces[4][1][1]) insert_blue_orange();
            else if(cube.faces[3][1][2]!=cube.faces[3][1][1] || cube.faces[5][2][1]!=cube.faces[5][1][1]) insert_green_orange();

                }
       
    }

    cout << endl;
    if(middleSolved())
        cout << "✅ Middle layer solved in " << sol.size() << " moves.\n";
    else
        cout << "⚠️ Partial middle layer after " << sol.size() << " moves.\n";
    return sol;
}


vector<string> solve_yellow_cross(Cube &cube){
    // Implementation for solving the yellow cross
    cout << "Solving yellow cross..." << endl;
    vector<string> solution;
    // Add your algorithm here
    return solution;
}
vector<string> solve_yellow_corners(Cube &cube){
    // Implementation for solving the yellow corners
    cout << "Solving yellow corners..." << endl;
    vector<string> solution;
    // Add your algorithm here
    return solution;
}



void solver(Cube &cube) {
    // Implementation of the solver function
    // This is a placeholder for the actual solving algorithm
    // cube.display();
    vector<string> s1, s2, s3, s4, s5;
    s1 = solve_white_cross(cube);
    cube.display();

    s2 = solve_white_corners(cube);
    cube.display();
    s3 = solve_middle_layer(cube);
    // s4 = solve_yellow_cross(cube);
    // s5 = solve_yellow_corners(cube);

    cube.display();
}




int main() {
    // Cube cube;
    srand(time(0));
    string input_str = "wwwwwwwwwyyyyyyyyyrrrrrrrrrooooooooobbbbbbbbbggggggggg";
    Cube c1;
    cube_input(c1, input_str);
    c1.display();
    // c1.shufflecube_random(20);
    // c1.display();
    c1.shufflecube_random(20);
    c1.display();
    solver(c1);
    c1.display();

    return 0;
}