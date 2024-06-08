/**
 *  @file        board-private.h
 *  @description Student-defined functions of Board class, for CPSC 221 PA2
 *
 */

template <template <class T> class Quack>
void recurs_maze(Quack<pair<int, int>> &sol, set<pair<int, int>> &v);