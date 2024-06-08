#include "cell.h"

/**
 * Cell constructor. Initializes all walls to be true and path_dist_from_start to 0.
 * @param QR Axial coordinates of the  cell
 */
Cell::Cell(std::pair<int, int> QR)
{
    path_dist_from_start = 0;
    for (int i = 0; i < 6; i++)
    {
        walls[i] = true;
    }
    qr = QR;
}

/**
 * Gets the side of a neighbour. Each side is represented with an int in [0,5].
 * See above for the definition of the sides
 * @param cell A neighbouring Cell
 * @return The side of cell
 * REQUIRE: cell is a neighbour of this cell
 */
int Cell::get_neighbour_side(const Cell *cell) const
{

    if (cell->qr.first == qr.first)
    {
        if (cell->qr.second < qr.second)
        {
            return 0;
        }
        return 3;
    }
    if (cell->qr.first < qr.first)
    {
        if (cell->qr.second > qr.second)
        {
            return 4;
        }
        return 5;
    }
    if (cell->qr.first > qr.first)
    {
        if (cell->qr.second < qr.second)
        {
            return 1;
        }
        return 2;
    }
}
