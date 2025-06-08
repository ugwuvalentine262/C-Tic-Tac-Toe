#pragma once

#include "position.hpp"
#include "movegen.hpp"

/// this class handles the search procedure of the
/// game. it performs a negamax search on the given
/// tic-tac-toe Position, and returns the best of
/// that Position.

class NegaMax
{

private:

  // a reference to a Position object.
  Position& pos__;

public:

  // calls the alpha-beta routine on the
  // Position and returns the move(best) suggested
  // by the search.
  int search()
  {
    int __best_move = -1;

    NegaMax::search(-1000, 1000, __best_move);

    return __best_move;
  }

private:
  // this is the alpha-beta search routine.
  // searches the Position to it's leaf node, and returns
  // score of the resulting best-move. since tic-tac-toe has a
  // small state-space, we can search all the maximum depth.
  int search(int __alpha, int __beta, int& __best_move, int ply=0)
  {
    // terminal position?
    if (pos__.terminal())
    {
      // return the current evaluation of the Position
      // with respect to the current side to move.
      // prefer shorter wins to longer ones.
      return !pos__.winner() ? 0 : -1000 + ply;
    }

    for (Tile __tile : MoveGen(pos__))
    {
      int __move = __tile;
      pos__.make_move(__move);

      auto v = -search(-__beta, -__alpha, __tile, ply+1);

      pos__.unmake_move(__move);

      if (v > __alpha)
      {
        // this move caused a cutoff
        if (v >= __beta)
        {
          return __beta;
        }
        // update best-move;
        __best_move = __move;
        // update alpha
        __alpha = v;
      }
    }
    return __alpha;
  }

public:

  // constructor initializes the object
  // with the Position; to search.
  NegaMax(Position& __pos)
    : pos__(__pos)
  {}
};
