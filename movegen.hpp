#pragma once

#include <algorithm>

/// this class receives a tic-tac-toe Position as
/// input, and returns all the legal moves of that
/// Position.

class MoveGen
{

private:

  // this is the list where the moves
  // to be generated will be stored.
  int list__[10];

  // a pointer to the last element of the
  // moves to be generated.
  int *last__;

public:

  // member function returns true if the
  // move-list is no empty.
  inline operator bool() const
  {
    return (last__ - list__) == 0;
  }

  // returns a read-only iterator, referencing
  // the first element of the move-list.
  const int *begin() const
  {
    return list__;
  }

  // returns a read-only iterator, pointing to
  // the end of the move-list.
  const int *end() const
  {
    return last__;
  }

  // returns 1 if the specified move
  // is contained in the move-list.
  int count(int m)
  {
    return std::find(list__, last__, m) != last__;
  }

  // constructor receives a Position object as
  // inputs, and generates all legal moves for that
  // given Position.
  MoveGen(const Position& __pos)
    : list__ {}, last__(list__)
  {
    constexpr Tile __tiles [] {0, 1, 2, 3, 4, 5, 6, 7, 8};

    for (const auto& __tile : __tiles)
    {
      if (!__pos.stone_on(__tile))
      {
        *last__++ = __tile;
      }
    }
  }
};
