#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>
#include <string>

class Cube {
public:
    std::vector<std::vector<char>> faces[6];

    Cube();

    void display();
    void shufflecube_random(int moves);
    void applymove(std::string move);

    // Moves
    void move_R();  void move_Ri();
    void move_L();  void move_Li();
    void move_U();  void move_Ui();
    void move_D();  void move_Di();
    void move_F();  void move_Fi();
    void move_B();  void move_Bi();
};

#endif
