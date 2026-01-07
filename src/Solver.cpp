#include "Solver.hpp"
#include "Utils.hpp"
#include <iostream>
#include <map>
#include <functional>
#include <algorithm>
using namespace std;

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

    auto ordered_moves = [&](Cube &c, const string &last)->vector<string>{
        struct Cand{ string m; int sc; };
        vector<Cand> cand; cand.reserve(MOVES.size());
        for(const auto &m: MOVES){
            if(!last.empty()){
                if(faceOf(m)==faceOf(last)) continue;             
                if(inverseMove(last)==m) continue;                    
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
    int startScore = cross_score(cube);
    int minDepth = max(0, 4 - startScore);
    int maxDepth = 16; 
    bool found = false;

    for(int depth=minDepth; depth<=maxDepth && !found; ++depth){
        vector<string> path;
        Cube start = cube;
        if(dfs(start, depth, "", path)){
            
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


vector<string> reversePattern(const vector<string>& p) {
    vector<string> r = p;
    reverse(r.begin(), r.end());
    return r;
}


bool matches(const vector<string>& v, int start,
             const vector<string>& pattern, int times) {
    int len = pattern.size();
    if (start + len * times > (int)v.size()) return false;

    for (int t = 0; t < times; t++) {
        for (int j = 0; j < len; j++) {
            if (v[start + t * len + j] != pattern[j])
                return false;
        }
    }
    return true;
}



void compressMoves(vector<string>& moves) {

    vector<vector<string>> patterns = {
        {"R","B","R'","B'"},
        {"U","B","U'","B'"},
        {"L","B","L'","B'"},
        {"D","B","D'","B'"}
    };

    for (int i = 0; i < (int)moves.size(); ) {
        bool changed = false;

        for (auto& pat : patterns) {

            // Rule 1: 6 repetitions → delete
            if (matches(moves, i, pat, 6)) {
                moves.erase(
                    moves.begin() + i,
                    moves.begin() + i + 6 * pat.size()
                );
                changed = true;
                break;
            }

            // Rule 2: 5 repetitions → replace with reverse
            if (matches(moves, i, pat, 5)) {
                auto rev = reversePattern(pat);
                moves.erase(
                    moves.begin() + i,
                    moves.begin() + i + 5 * pat.size()
                );
                moves.insert(moves.begin() + i, rev.begin(), rev.end());
                changed = true;
                break;
            }
        }

        if (!changed) i++; 
    }
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
        

       while(cube.faces[4][0][2]==cube.faces[4][1][2] && cube.faces[2][2][0]==cube.faces[2][2][1]){
            seq({"F"});
       }       
       if(cube.faces[4][0][0]!=cube.faces[0][1][1] && cube.faces[2][0][0]!=cube.faces[0][1][1] ){
            c1 = cube.faces[4][0][2];
            c2 = cube.faces[2][2][0];
            seq({"L'","B","L"});
       }
       while (true){
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
    compressMoves(sol);
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

    auto edgehas_yellow =[&](char a,char bb){ return a=='y' || bb=='y'; };

    auto insert_red_blue  =[&](){ seq({"B'","L'","B","L","B","U","B'","U'"}); };
    auto insert_blue_red  =[&](){ seq({"B","U","B'","U'","B'","L'","B","L"}); };
    auto insert_green_orange=[&](){ seq({"B","D","B'","D'","B'","R'","B","R"}); };
    auto insert_orange_green=[&](){ seq({"B'","R'","B","R","B","D","B'","D'"}); };
    auto insert_green_red =[&](){ seq({"B'","U'","B","U","B","R","B'","R'"}); };
    auto insert_red_green =[&](){ seq({"B","R","B'","R'","B'","U'","B","U"}); };

    auto insert_blue_orange=[&](){ seq({"B'","D'","B","D","B","L","B'","L'"}); };
    auto insert_orange_blue=[&](){ seq({"B","L","B'","L'","B'","D'","B","D"}); };

    while(!middleSolved()){

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
            else if(front=='o'){
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
            else if(front=='o'){
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
            else if(front=='o'){
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
            else if(front=='o'){
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
                     if(cube.faces[2][1][2]!=cube.faces[2][1][1] || cube.faces[5][0][1]!=cube.faces[5][1][1]) insert_red_green();
            else if(cube.faces[2][1][0]!=cube.faces[2][1][1] || cube.faces[4][0][1]!=cube.faces[4][1][1]) insert_red_blue();
            else if(cube.faces[3][1][0]!=cube.faces[3][1][1] || cube.faces[4][2][1]!=cube.faces[4][1][1]) insert_blue_orange();
            else if(cube.faces[3][1][2]!=cube.faces[3][1][1] || cube.faces[5][2][1]!=cube.faces[5][1][1]) insert_green_orange();

                }
       
    }

    cout << endl;
    if(middleSolved())
        cout << "Middle layer solved in " << sol.size() << " moves.\n";
    else
        cout << "Partial middle layer after " << sol.size() << " moves.\n";
    return sol;
}


vector<string> solve_yellow_cross(Cube &cube){
    // Implementation for solving the yellow cross
    vector<string> solution;
    auto add=[&](string m){ cube.applymove(m); solution.push_back(m); cout<<m<<" "; };
    auto seq=[&](vector<string> moves){ for(auto &m:moves) add(m); };
    cout << "Solving yellow cross..." << endl;
    auto has_yellow =[&](char a){ return a=='y' ; };
    auto crossyellow=[&](){
        bool ok=true;
        if(cube.faces[1][0][1]!=cube.faces[1][1][1] ||
            cube.faces[1][1][0]!=cube.faces[1][1][1] ||
            cube.faces[1][1][2]!=cube.faces[1][1][1] ||
            cube.faces[1][2][1]!=cube.faces[1][1][1] ) ok=false;
        
        return ok;
    };
    while(!crossyellow()){
        char e1 = cube.faces[1][0][1];
        char e2 = cube.faces[1][1][0];
        char e3 = cube.faces[1][2][1];
        char e4 = cube.faces[1][1][2];
        if(!has_yellow(e1) && !has_yellow(e2) && !has_yellow(e3) && !has_yellow(e4) ){
            seq({"U","R","B","R'","B'","U'"});
        }
        else if(!has_yellow(e1)&&!has_yellow(e2)&&has_yellow(e3)&&has_yellow(e4)){
            seq({"U","R","B","R'","B'","U'"});
        }
        else if(!has_yellow(e1)&&has_yellow(e2)&&has_yellow(e3)&&!has_yellow(e4)){
            seq({"B'","U","R","B","R'","B'","U'"});
        }
        else if(has_yellow(e1)&&has_yellow(e2)&&!has_yellow(e3)&&!has_yellow(e4)){
            seq({"B2","U","R","B","R'","B'","U'"});
        }
        else if(has_yellow(e1)&&!has_yellow(e2)&&!has_yellow(e3)&&has_yellow(e4)){
            seq({"B","U","R","B","R'","B'","U'"});
        }
        else if(!has_yellow(e1)&&has_yellow(e2)&&!has_yellow(e3)&&has_yellow(e4)){
            seq({"U","R","B","R'","B'","U'"});
        }
        else if(has_yellow(e1)&&!has_yellow(e2)&&has_yellow(e3)&&!has_yellow(e4)){
            seq({"B","U","R","B","R'","B'","U'"});
        }
    }
    cout<<endl;
    if(crossyellow()){
        cout << " Last layer cross solved in " << solution.size() << " moves." << endl;
    } else {
        cout << " Failed to complete within limit. Progress " << endl;
    }

    return solution;
}
vector<string> solve_yellow_corners(Cube &cube){
    // Implementation for solving the yellow corners
    cout << "Solving yellow midpieces..." << endl;
    vector<string> solution;
    auto add=[&](string m){ cube.applymove(m); solution.push_back(m); cout<<m<<" "; };
    auto seq=[&](vector<string> moves){ for(auto &m:moves) add(m); };

    auto issolved=[&](){
        bool ok=false;
        if((cube.faces[2][0][1]=='r' && cube.faces[5][1][2]=='g'   && cube.faces[3][2][1]=='o' && cube.faces[4][1][0]=='b') ||
            (cube.faces[2][0][1]=='g' && cube.faces[5][1][2]=='o'   && cube.faces[3][2][1]=='b' && cube.faces[4][1][0]=='r') ||
            (cube.faces[2][0][1]=='o' && cube.faces[5][1][2]=='b'   && cube.faces[3][2][1]=='r' && cube.faces[4][1][0]=='g') ||
            (cube.faces[2][0][1]=='b' && cube.faces[5][1][2]=='r'   && cube.faces[3][2][1]=='g' && cube.faces[4][1][0]=='o') ) ok=true;
        
        return ok;
    };

    
    while(!issolved()){
        
        char rs = cube.faces[2][0][1];
        char bs = cube.faces[4][1][0];
        char gs = cube.faces[5][1][2];
        char os = cube.faces[3][2][1];
        if((rs=='r' && os=='o')){
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(rs=='o' && os=='r'){
            seq({"B2"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(rs=='b' && os=='g'){
            seq({"B"});
        }
        else if(rs=='g' && os=='b'){
            seq({"B"});
        }
        else if(rs=='r' && gs=='g'){
            seq({"B2"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(gs=='r' && os=='g'){
            seq({"B'"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(os=='r' && bs=='g'){
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(bs=='r' && rs=='g'){
            seq({"B"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(rs=='g' && gs=='o'){
            seq({"B2"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(gs=='g' && os=='o'){
            seq({"B'"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(os=='g' && bs=='o'){
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(bs=='g' && rs=='o'){
            seq({"B"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(rs=='o' && gs=='b'){
            seq({"B2"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(gs=='o' && os=='b'){
            seq({"B'"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(os=='o' && bs=='b'){
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(bs=='o' && rs=='b'){
            seq({"B"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(rs=='b' && gs=='r'){
            seq({"B2"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(gs=='b' && os=='r'){
            seq({"B'"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(os=='b' && bs=='r'){
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        else if(bs=='b' && rs=='r'){
            seq({"B"});
            seq({"R","B","B","R'","B'","R","B'","R'"});
        }
        
    }

    cout << endl << "Solving yellow corners..." << endl;
    auto issettled=[&](){
        char rs = cube.faces[2][0][1];
        char gs = cube.faces[5][1][2];
        char os = cube.faces[3][2][1];
        char bs = cube.faces[4][1][0];

        string act_c1 = string() + rs + gs + cube.faces[1][1][1];
        string act_c2 = string() + os + gs + cube.faces[1][1][1];
        string act_c3 = string() + os + bs + cube.faces[1][1][1];
        string act_c4 = string() + rs + bs + cube.faces[1][1][1];
        sort(act_c1.begin(),act_c1.end());
        sort(act_c2.begin(),act_c2.end());
        sort(act_c3.begin(),act_c3.end());
        sort(act_c4.begin(),act_c4.end());
        
        char c11 = cube.faces[2][0][2];
        char c12 = cube.faces[1][0][0];
        char c13 = cube.faces[5][0][2];
        string c1 = string() + c11 + c12 + c13;
        sort(c1.begin(),c1.end());

        char c21 = cube.faces[1][2][0];
        char c22 = cube.faces[3][2][2];
        char c23 = cube.faces[5][2][2];
        string c2 = string() + c21 + c22 + c23;
        sort(c2.begin(),c2.end());


        char c31 = cube.faces[1][2][2];
        char c32 = cube.faces[3][2][0];
        char c33 = cube.faces[4][2][0];
        string c3 = string() + c31 + c32 + c33;
        sort(c3.begin(),c3.end());


        char c41 = cube.faces[2][0][0];
        char c42 = cube.faces[1][0][2];
        char c43 = cube.faces[4][0][0];
        string c4 = string() + c41 + c42 + c43;
        sort(c4.begin(),c4.end());


        if(act_c1==c1 && act_c2==c2 && act_c3==c3 && act_c4==c4) return true;
        return false;
    };

    while(!issettled()){
        char rs = cube.faces[2][0][1];
        char gs = cube.faces[5][1][2];
        char os = cube.faces[3][2][1];
        char bs = cube.faces[4][1][0];

        string act_c1 = string() + rs + gs + cube.faces[1][1][1];
        string act_c2 = string() + os + gs + cube.faces[1][1][1];
        string act_c3 = string() + os + bs + cube.faces[1][1][1];
        string act_c4 = string() + rs + bs + cube.faces[1][1][1];
        sort(act_c1.begin(),act_c1.end());
        sort(act_c2.begin(),act_c2.end());
        sort(act_c3.begin(),act_c3.end());
        sort(act_c4.begin(),act_c4.end());
        
        char c11 = cube.faces[2][0][2];
        char c12 = cube.faces[1][0][0];
        char c13 = cube.faces[5][0][2];
        string c1 = string() + c11 + c12 + c13;
        sort(c1.begin(),c1.end());

        char c21 = cube.faces[1][2][0];
        char c22 = cube.faces[3][2][2];
        char c23 = cube.faces[5][2][2];
        string c2 = string() + c21 + c22 + c23;
        sort(c2.begin(),c2.end());


        char c31 = cube.faces[1][2][2];
        char c32 = cube.faces[3][2][0];
        char c33 = cube.faces[4][2][0];
        string c3 = string() + c31 + c32 + c33;
        sort(c3.begin(),c3.end());


        char c41 = cube.faces[2][0][0];
        char c42 = cube.faces[1][0][2];
        char c43 = cube.faces[4][0][0];
        string c4 = string() + c41 + c42 + c43;
        sort(c4.begin(),c4.end());

        if(act_c1==c1){
            seq({"L'","B","R","B'","L","B","R'","B'"});
        }
        else if(act_c2==c2){
            seq({"B"});
            seq({"L'","B","R","B'","L","B","R'","B'"});
        }
        else if(act_c3==c3){
            seq({"B2"});
            seq({"L'","B","R","B'","L","B","R'","B'"});
        }
        else if(act_c4==c4){
            seq({"B'"});
            seq({"L'","B","R","B'","L","B","R'","B'"});
        }
        else {
            seq({"L'","B","R","B'","L","B","R'","B'"});
        }
    }

cout<<endl;

    while(1){
        char cy1 = cube.faces[1][0][0];
        char cy2 = cube.faces[1][2][0];
        char cy3 = cube.faces[1][2][2];
        char cy4 = cube.faces[1][0][2];
        if(cy1!='y'){
            if(cube.faces[2][0][2]=='y')seq({"R'","F","R","F'","R'","F","R","F'"});
            else seq({"R'","F","R","F'","R'","F","R","F'","R'","F","R","F'","R'","F","R","F'"});
        }
        else if(cy2!='y'){
            seq({"B"});
            if(cube.faces[2][0][2]=='y')seq({"R'","F","R","F'","R'","F","R","F'"});
            else seq({"R'","F","R","F'","R'","F","R","F'","R'","F","R","F'","R'","F","R","F'"});
        }
        else if(cy3!='y'){
            seq({"B2"});
            if(cube.faces[2][0][2]=='y')seq({"R'","F","R","F'","R'","F","R","F'"});
            else seq({"R'","F","R","F'","R'","F","R","F'","R'","F","R","F'","R'","F","R","F'"});
        }
        else if(cy4!='y'){
            seq({"B'"});
            if(cube.faces[2][0][2]=='y')seq({"R'","F","R","F'","R'","F","R","F'"});
            else seq({"R'","F","R","F'","R'","F","R","F'","R'","F","R","F'","R'","F","R","F'"});
        }
        if(cy1=='y' &&cy2=='y' &&cy3=='y' &&cy4=='y') break;
    }
    while(cube.faces[2][0][1]!=cube.faces[2][1][1]) seq({"B"});








    cout<<endl;
    if(issettled()){
        cout << " Last layer solved in " << solution.size() << " moves." << endl;
    } else {
        cout << " Failed to complete within limit. Progress " << endl;
    }
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
    cube.display();
    s4 = solve_yellow_cross(cube);
    cube.display();
    s5 = solve_yellow_corners(cube);
    cube.display();
    int sum = s1.size()+s2.size()+s3.size()+s4.size()+s5.size(); 

    cout << "*********** White cross solved in " << s1.size() << " moves. *****************" << endl;
    cout << "*********** White corners solved in " << s2.size() << " moves. ***************" << endl;
    cout << "*********** Middle layer solved in " << s3.size() << " moves. ****************" << endl;
    cout << "*********** Third layer cross solved in " << s4.size() << " moves. ***********" << endl;
    cout << "*********** Last layer solved in " << s5.size() << " moves. ******************" << endl <<endl;
    cout << "*********** Full cube solves in " << sum << " moves. ******************" <<endl; 



}
