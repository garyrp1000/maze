#include "maze.h"
#include <vector>
#include <fstream>
#include <cstdlib> // For std::rand, std::srand
#include <ctime>   // For seeding randomness

// Constructor: Initializes the maze with seed, rows, and columns
Maze::Maze(int seed, int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<int>(cols, 15)) {
    std::srand(seed);  // Seed the random number generator
}

// Generate the maze using a randomized depth-first search (DFS) approach
void Maze::generate() {
    std::vector<std::pair<int, int>> stack;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    stack.push_back({0, 0});
    visited[0][0] = true;

    while (!stack.empty()) {
        // Get current cell (last from the stack)
        auto [x, y] = stack.back();
        stack.pop_back();

        // Get list of unvisited neighbors
        std::vector<std::pair<int, int>> neighbors = getNeighbors(x, y);

        if (!neighbors.empty()) {
            // Push current cell back onto the stack
            stack.push_back({x, y});

            // Pick a random neighbor and remove the wall between
            int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
            auto [nx, ny] = neighbors[idx];

            removeWall(x, y, nx, ny);
            visited[nx][ny] = true;
            stack.push_back({nx, ny});
        }
    }

    // Remove the top wall from the start and the bottom wall from the end
    grid[0][0] &= ~1;               // Remove north wall from start (0, 0)
    grid[rows - 1][cols - 1] &= ~4; // Remove south wall from end (n-1, m-1)
}

// Get all unvisited neighbors of a cell
std::vector<std::pair<int, int>> Maze::getNeighbors(int x, int y) {
    std::vector<std::pair<int, int>> neighbors;

    if (x > 0 && grid[x - 1][y] == 15) {  // North
        neighbors.push_back({x - 1, y});
    }
    if (x < rows - 1 && grid[x + 1][y] == 15) { // South
        neighbors.push_back({x + 1, y});
    }
    if (y > 0 && grid[x][y - 1] == 15) {  // West
        neighbors.push_back({x, y - 1});
    }
    if (y < cols - 1 && grid[x][y + 1] == 15) { // East
        neighbors.push_back({x, y + 1});
    }

    return neighbors;
}

// Remove the wall between two cells
void Maze::removeWall(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2 + 1) {  // West
        grid[x1][y1] &= ~8; // Remove west wall of current
        grid[x2][y2] &= ~2; // Remove east wall of neighbor
    } else if (x1 == x2 && y1 == y2 - 1) {  // East
        grid[x1][y1] &= ~2;
        grid[x2][y2] &= ~8;
    } else if (x1 == x2 + 1 && y1 == y2) {  // North
        grid[x1][y1] &= ~1;
        grid[x2][y2] &= ~4;
    } else if (x1 == x2 - 1 && y1 == y2) {  // South
        grid[x1][y1] &= ~4;
        grid[x2][y2] &= ~1;
    }
}

// Save the maze to a file
void Maze::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file << grid[i][j];
                if (j < cols - 1) file << " "; // Add space between columns
            }
            file << "\n";
        }
        file.close();
    }
}
