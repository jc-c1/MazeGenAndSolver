#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <utility>

#include "cs221util/RGBAPixel.h"

// Sides
const int N = 0;
const int NE = 1;
const int SE = 2;
const int S = 3;
const int SW = 4;
const int NW = 5;

class Cell {
    public:
        // Axial coordinates of the cell
        std::pair<int, int> qr;

        // Path distance between the cell and the start coordinate in the maze
        int path_dist_from_start;

        // Walls are true to indicate there is a wall at the corresponding side of this cell
        bool walls[6];

        /**
         * Cell constructor. Initializes all walls to be true and path_dist_from_start to 0.
         * @param QR Axial coordinates of the  cell
         */
        Cell(std::pair<int, int> QR);

        /**
         * Gets the side of a neighbour. Each side is represented with an int in [0,5].
         * See above for the definition of the sides
         * @param cell A neighbouring Cell
         * @return The side of cell
         * REQUIRE: cell is a neighbour of this cell
         */
        int get_neighbour_side(const Cell* cell) const;

    private:
        /**************************************************************************************/
        /* IF YOU WISH TO DEFINE ANY PRIVATE MEMBER FUNCTIONS, ADD THEM TO cell-private.h  */
        /**************************************************************************************/
    #include "cell-private.h"
    
};

#endif