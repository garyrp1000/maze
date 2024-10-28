#include "maze.h"
#include <iostream>
#include <cstdlib> // For std::atoi

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <seed> <N> <M> <fname>" << std::endl;
        return 1;
    }

    int seed = std::atoi(argv[1]);
    int N = std::atoi(argv[2]);
    int M = std::atoi(argv[3]);
    std::string fname = argv[4];

    if (N <= 0 || M <= 0) {
        std::cerr << "Error: Rows and columns must be greater than 0." << std::endl;
        return 1;
    }

    // Create the maze, generate it, and save it to a file
    Maze maze(seed, N, M);
    maze.generate();
    maze.saveToFile(fname);

    return 0;
}
