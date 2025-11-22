# Rubik’s Cube Solver (C++)

A complete Rubik’s Cube solver written in **C++**, using a custom cube model, realistic move simulation, and full layer-by-layer solving logic.  
This solver displays the cube in the terminal using colored output and automatically solves any valid scramble.

---

## 🚀 Features

✔ Full cube simulation (all 18 moves: R L U D F B + inverses + double turns)  
✔ Colored terminal display using ANSI color codes  
✔ Random shuffle generator  
✔ Complete solving pipeline (White Cross → Corners → Middle Layer → Yellow Cross → Yellow Corners → PLL)  
✔ Step-by-step printed moves  
✔ Custom algorithms adapted to this cube orientation  
✔ IDDFS (Iterative Deepening DFS) for optimal white cross

---

## 🧠 Algorithms Implemented

### **Cube Representation**
- Each face stored as `vector<vector<char>> faces[6]`
- Custom rotation logic for every move  
- White = Front, Yellow = Back, Red = Top, Orange = Bottom, Blue = Left, Green = Right

### **Solving Stages**
1. **White Cross**  
   - IDDFS search with pruning  
2. **White Corners**  
   - Orientation + permutation  
3. **Middle Layer (F2L edges)**  
   - Left/right insert algorithms  
4. **Yellow Cross (OLL edges)**  
   - Edge-orientation algorithm  
5. **Yellow Corners (OLL corners)**  
   - Sune & Anti-Sune (rotated for this cube orientation)  
6. **Yellow Corner Permutation (PLL corners)**  
   - Corner 3-cycle algorithm  

---

## 🖥️ How to Run

### **1. Clone the repository**
```bash
git clone https://github.com/prashantbatchu/Rubiks_cube_solver_manually
cd Rubiks_cube_solver_manually
```

### **2. Compile**
```bash
g++ -std=c++17 main.cpp -o cube
```

### **3. Run**
```bash
./cube
```

---

## 📸 Example Output

```
Scramble: U R B' L2 D ...
Solving white cross...
Solving white corners...
Solving middle layer...
Solving yellow cross...
Solving yellow corners...
Cube solved!
```

---

## 🛠 Skills Demonstrated
- C++ (STL, classes, algorithms)
- IDDFS (search algorithm)
- State modeling
- Algorithm design (CFOP-based)
- Debugging complex systems
- Git & GitHub

---

## 📂 Project Structure

```
main.cpp
Cube class
Solver logic
README.md
```

---

## 📄 License
MIT License
