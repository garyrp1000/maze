#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
public:
        Maze(int seed, int rows, int cols);
        void generate();
        void saveToFile(const std::string& filename);

private:
        int rows, cols;
        std::vector<std::vector<int>> grid; // 2D grid for the maze
        std::vector<std::pair<int, int>> getNeighbors(int x, int y);
        void removeWall(int x1, int y1, int x2, int y2);
        void initializeGrid();
};

#endif // MAZE_H
