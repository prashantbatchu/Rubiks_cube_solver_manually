# Rubik’s Cube Solver (C++)

A complete Rubik’s Cube solver written in **C++**, using a custom cube model, realistic move simulation, and full layer-by-layer solving logic.  
This solver displays the cube in the terminal using colored output and automatically solves any valid scramble.

---



## 🧩 Cube Solver Demo

![Demo of solving cube](assets/Screen%20Recording%202026-01-07%20193304.mp4)

## ✨ Features

- 🎨 **Colored cube display** in terminal using ANSI escape codes  
- 🔀 **Random cube shuffling**
- 🔁 Supports all standard cube moves:
  - `R L U D F B`
  - Inverse moves: `R' L' U' D' F' B'`
  - Double moves: `R2 L2 U2 D2 F2 B2`
- 🧠 **Automatic solver** with the following stages:
  1. White Cross (IDDFS + heuristic)
  2. White Corners
  3. Middle Layer
  4. Yellow Cross
  5. Yellow Corners
- 🧱 **Fully object-oriented design**
- 📦 Modular file structure (`.hpp` and `.cpp`)


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
