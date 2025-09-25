# AI Algorithms

This repository contains small C/C++ projects exploring classic AI and pathfinding techniques.

## 📂 Projects

- **pacman/**  
  A grid-based Pacman exercise with implementations of search and pathfinding algorithms.

- **maze meet up/**  
  Maze problem focused on meeting paths and navigation.

- **maze runner/**  
  Maze-solving exercise demonstrating pathfinding in different layouts.

## ⚙️ Build and Run

### Windows (MSVC)
```bat
cd pacman
cl /std:c++17 /O2 /EHsc /Fe:pacman.exe *.cpp
pacman.exe
```

### Linux/macOS (GCC/Clang)
```bash
cd pacman
g++ -std=c++17 -O2 -o pacman *.cpp
./pacman
```

(Adjust the compile commands depending on which project folder you want to build.)

## 🧠 Algorithms Covered

- **Breadth-First Search (BFS)**  
- **Depth-First Search (DFS)**  
- **A*** search with heuristics (e.g., Manhattan distance)

## 📁 Repository Structure

```
ai-algorithms/
├─ pacman/        # Pacman AI/pathfinding project
├─ maze meet up/  # Maze meet-up project
├─ maze runner/   # Maze runner project
├─ .gitignore
├─ .gitattributes
└─ README.md
```

