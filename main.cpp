#include <iostream>

#include "drawmaze.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main() {
    // set rng seed for choose_neighbour
    int seed = 10;

    // create board
    Board board(5);

    // size of agon for drawing
    int size = 20;

    board.generate_maze({0, 0}, 0.5, seed);

    PNG output = DrawMaze::draw_maze(board, size, "none");
    output.writeToFile("maze.png");

    output = DrawMaze::draw_maze(board, size, "path");
    output.writeToFile("maze coloured based on path distance.png");

    board.solve_maze();

    output = DrawMaze::draw_solution(board, size, "none");
    output.writeToFile("maze with solutions.png");

    cout << board.longest_path_dist << endl;
    cout << board.solution.size() << endl;

    output = DrawMaze::draw_solution(board, size, "path");
    output.writeToFile("maze with solutions coloured based on path distance.png");
}
