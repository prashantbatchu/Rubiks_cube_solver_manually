#include "solve.hpp"
// #include "main.cpp"


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

string getStateString(const Cube &cube){
    string state="";
    for(int i=0;i<6;i++){   
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                state.push_back(cube.faces[i][j][k]);
            }
        }
    }
    return state;
}


void solver(Cube &cube) {
    // Implementation of the solver function
    // This is a placeholder for the actual solving algorithm
    cube.display();
    vector<string> s1, s2, s3, s4, s5;
    s1 = solve_white_cross(cube);
    // s2 = solve_white_corners(cube);
    // s3 = solve_middle_layer(cube);
    // s4 = solve_yellow_cross(cube);
    // s5 = solve_yellow_corners(cube);

    cube.display();
}



vector<string> solve_white_cross(Cube &cube){
    // Implementation for solving the white cross
    cout << "Solving white cross..." << endl;
    vector<string> solution;

    queue<Cube> q;
    map<string, string> path; //state->path
    set<string> visited;

    string start_state = getStateString(cube); 

    q.push(cube);
    visited.insert(start_state);
    path[start_state] = ""; // The path for the start state is empty 

    vector<string> move_options = {"F", "R", "U", "L", "B", "D", "F'", "R'", "U'", "L'", "B'", "D'"};

    while (!q.empty()) {
        Cube current_cube = q.front();
        q.pop();

        if (is_white_cross_solved(current_cube)){
            // Reconstruct the solution path
            string moves_str = path[getStateString(current_cube)];
            stringstream ss(moves_str);
            string move;
            while (ss >> move) solution.push_back(move);

            for (auto &m : solution) cube.applymove(m);

            return solution;
        }

        string current_state_str = getStateString(current_cube);

        for (const string& move : move_options){
            Cube next_cube = current_cube;
            next_cube.applymove(move);
            string next_state_str = getStateString(next_cube);

            if (visited.find(next_state_str) == visited.end()) {
                visited.insert(next_state_str);
                path[next_state_str] = path[current_state_str] + (path[current_state_str] == "" ? move : " " + move);

                q.push(next_cube);
            }
        }

    }
}


vector<string> solve_white_corners(Cube &cube){
    // Implementation for solving the white corners
    cout << "Solving white corners..." << endl;
    vector<string> solution;
    // Add your algorithm here
    return solution;
}
vector<string> solve_middle_layer(Cube &cube){
    // Implementation for solving the middle layer
    cout << "Solving middle layer..." << endl;
    vector<string> solution;
    // Add your algorithm here
    return solution;
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



int main(){
    return 0;
}