#include "board.h"

#include <iostream>

#include "queue.h"
#include "stack.h"
#include "quack.h"

/**
 * Constructor. Creates a board with given radius, creating new Cells and inserting them into this->cells by calling createBoard().
 * The default start_coord and end_coord are (0, 0).
 * @note There is no maze yet! The board is just a beehive for now.
 * @param rad The radius of the board
 */
Board::Board(int rad)
{
    this->radius = rad;
    create_board();
    start_coord = {0, 0};
    end_coord = {0, 0};
    longest_path_dist = 0;
}

// Frees all dynamically allocated memory associated with the board.
Board::~Board()
{
    for (auto c : cells)
    {
        delete c.second;
    }
}

/**
 * Creates all necessary Cells up to the given radius and insert them into this->cells.
 */
void Board::create_board()
{
    int r = radius + 1;
    int i = 0;
    while (r)
    {
        int count = -radius;

        while (count < r)
        {
            if (i)
            {
                Cell *pos = new Cell({i, count});
                Cell *neg = new Cell({-i, -count});

                this->cells[{i, count}] = pos;
                this->cells[{-i, -count}] = neg;
            }
            else
            {
                Cell *z = new Cell({0, count});

                this->cells[{0, count}] = z;
            }
            count++;
        }
        r--;
        i++;
    }
}

/**
 * Gets the coordinates of the six neighbours of coord, in the sides order specified in Cell.h.
 * @param coord The input coordinate.
 */
vector<pair<int, int>> Board::get_neigh_coords(const pair<int, int> &coord) const
{
    vector<pair<int, int>> v;
    int q = coord.first;
    int r = coord.second;

    v.push_back({q, r - 1});
    v.push_back({q + 1, r - 1});
    v.push_back({q + 1, r});
    v.push_back({q, r + 1});
    v.push_back({q - 1, r + 1});
    v.push_back({q - 1, r});

    return v;
}

/**
 * Link two cells at the given coordinates by setting each cell's wall to false in the other cell's direction.
 * @param coord1 A coordinate of a Cell to be linked.
 * @param coord2 A coordinate of a Cell to be linked.
 * @note remember to link both directions!
 * REQUIRE: the two coords are neighbours
 */
void Board::link(const pair<int, int> &coord1, const pair<int, int> &coord2) const
{

    auto cell1 = cells.find(coord1)->second;
    auto cell2 = cells.find(coord2)->second;

    int c1w = cell1->get_neighbour_side(cell2);
    int c2w = cell2->get_neighbour_side(cell1);

    cell1->walls[c1w] = false;
    cell2->walls[c2w] = false;
}

/**
 * @param coord1 A coordinate of a Cell
 * @param coord2 A coordinate of a Cell
 * @return The cell distance (ignoring walls) between coord1 and coord2.
 */
int Board::distance(const pair<int, int> &coord1, const pair<int, int> &coord2) const
{
    int q1 = coord1.first;
    int q2 = coord2.first;
    int r1 = coord1.second;
    int r2 = coord2.second;

    int c1 = q1 - q2;
    int c2 = r1 - r2;

    if (c1 * c2 <= 0)
    {
        return max(abs(c1), abs(c2));
    }
    else
    {
        return abs(c1) + abs(c2);
    }
}

/**
 * @return true if coord is at the edge of the board, false otherwise.
 */
bool Board::is_edge(const pair<int, int> &coord) const
{
    if (abs(coord.first) == radius || abs(coord.second) == radius || abs(coord.first + coord.second) == radius)
        return true;

    return false;
}

/**
 * Traverses the board via dfs to generate the maze, updating and keeping track of:
 * The largest path distance from start to an edge cell so far (this is not longest_path_dist!)

 * @param start The {q, r} coordinate of the start of the maze.
 * @param branch_prob Specifies how often it should "branch out" when choosing neighbours.
 *                    A small branch_prob means neighbours of the same dist from the start_coord are preferred
 *                    A large branch_prob means neighbours of a different dist from the start_coord are preferred
 * @param seed The seed used for the rng
 * REQUIRE: create_board() is already called
 */
void Board::generate_maze(pair<int, int> start, double branch_prob, int seed)
{

    start_coord = start;
    this->rng.seed(seed);
    Stack<pair<int, int>> s;
    set<pair<int, int>> v;

    s.push(start_coord);
    v.insert(start_coord);

    int dist_to_start = 0;

    cells[start]->path_dist_from_start = dist_to_start;

    while (!s.is_empty())
    {
        pair<int, int> curr_coord = s.peek();

        Cell *neigh_cell = choose_neighbour(curr_coord, v, branch_prob);

        if (neigh_cell)
        {
            link(neigh_cell->qr, curr_coord);
            s.push(neigh_cell->qr);
            v.insert(neigh_cell->qr);
            dist_to_start++;
            neigh_cell->path_dist_from_start = dist_to_start;
            if (dist_to_start > longest_path_dist)
            {
                longest_path_dist = max(longest_path_dist, dist_to_start);
                end_coord = neigh_cell->qr;
            }
        }
        else
        {
            dist_to_start--;
            s.pop();
        }
    }
}

template <template <class T> class Quack>
void Board::recurs_maze(Quack<pair<int, int>> &sol, set<pair<int, int>> &v)
{
    pair<int, int> curr_coord = sol.peekR();

    if (curr_coord == end_coord)
    {
        while (!sol.is_empty())
        {
            solution.push_back(sol.pop_left());
        }
        return;
    }
    else
    {

        Cell *curr = cells[curr_coord];
        int i = 0;
        vector<pair<int, int>> vs = get_neigh_coords(curr_coord);

        for (bool w : curr->walls)
        {
            // no wall and not visited and the cell exists
            if (!w && v.find(vs[i]) == v.end() && cells.find(vs[i]) != cells.end())
            {
                sol.push_right(vs[i]);
                v.insert(vs[i]);
                recurs_maze(sol, v);
                if (solution.size())
                {
                    return;
                }

                sol.pop_right();
            }
            i++;
        }
    }
}

/**
 * Populate (member variable) solution as a list of coordinates from start_coord to end_coord, represented as {q, r} pairs.

 * REQUIRE: generate_maze must be called already
 */
void Board::solve_maze()
{

    solution.clear();

    Quack<pair<int, int>> s;

    set<pair<int, int>> v;

    s.push_right(start_coord);

    v.insert(start_coord);

    recurs_maze(s, v);
}