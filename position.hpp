#pragma once

#include <iostream>

#define O -1
#define X 1

/// template meta-function returns the number of arguments in it's template parameters
/// that match the type of the first template parameter.

template<typename A, typename...>
constexpr unsigned TypeCount = 0;
template<typename A, typename B, typename ...C>
constexpr unsigned TypeCount<A, B, C...> = std::is_same<A, B>::value + TypeCount<A, C...>;

/// template meta-function returns the number of arguments in
/// it's template parameters.

template<typename ...>
constexpr unsigned ArgsCount = 0;
template<typename first, typename ...rest>
constexpr unsigned ArgsCount<first, rest...> = 1 + ArgsCount<rest...>;

/// forward declaration;
class Position;

// each Tile of the tic-tac-toe board is
// actually a signed integer.
using Tile = signed;

// function returns true if the Tile is okay.
// this is when the specified argument is within
// the range [0, 9).
inline bool tile_is_ok(Tile __tile)
{
  return __tile >= 0 && __tile <= 8;
}

/// this data-structure models a tic-tac-toe board.

class Position
{
  // the combination of squares that
  // make up the win positions.
  static
  constexpr Tile combs__[][3]
  {
    {0, 1, 2}
  , {3, 4, 5}
  , {6, 7, 8}
  , {0, 3, 6}
  , {1, 4, 7}
  , {2, 5, 8}
  , {0, 4, 8}
  , {2, 4, 6}
  };

private:

  // the tic-tac-toe board is actually represented
  // with an array of tiles.
  std::array<Tile, 9> tiles__ {};

public:

  // returns the winner of the current Position.
  // this will be 1 if it is X, -1 if it is O, and
  // 0 if the Position is neither a win nor a loss.
  signed winner() const
  {
    for (const auto& comb__ : combs__)

    if (   (tiles__[comb__[0]] != 0)
        && (tiles__[comb__[0]] == tiles__[comb__[1]])
        && (tiles__[comb__[0]] == tiles__[comb__[2]])
        )
    {
      return tiles__[comb__[0]];
    }
    return 0;
  }

  // returns the 1 if it is X's turn to move, and
  // -1 if it is O's turn to move.
  signed stone() const
  {
    return is_x() ? X : O;
  }

  // returns the stone on the specified Tile.
  signed stone_on(Tile __tile) const
  {
    return tiles__.at(__tile);
  }

  // makes a move on the current Position by
  // putting a piece of the side to on the given Tile.
  bool make_move(Tile __tile)
  {
    if (!tile_is_ok(__tile) || stone_on(__tile))
    {
      return false;
    }

    tiles__[__tile] = stone();

    return true;
  }

  // calling this function returns the Position to it's
  // previous state, before the make-move method
  // was called.
  bool unmake_move(Tile __tile)
  {
    if (!tile_is_ok(__tile) || !stone_on(__tile))
    {
      return false;
    }
    tiles__[__tile] = 0;

    return true;
  }

  // function returns true if the current Position
  // is a terminal Position.
  bool terminal() const
  {
    for (const auto& comb__ : combs__)

    if (   (tiles__[comb__[0]] != 0)
        && (tiles__[comb__[0]] == tiles__[comb__[1]])
        && (tiles__[comb__[0]] == tiles__[comb__[2]])
        )
    {
      return true;
    }

  return tiles__[0] && tiles__[1] && tiles__[2]
      && tiles__[3] && tiles__[4] && tiles__[5]
      && tiles__[6] && tiles__[7] && tiles__[8];
  }

  // member function returns true if it is X's turn
  // to move. otherwise it returns false.
  bool is_x() const
  {
    return count(X) == count(O) ? true : false;
  }

private:
  // returns the number of occurrences of the stone
  // of the specified type.
  int count(int __stone) const
  {
    return std::count(tiles__.begin(), tiles__.end(), __stone);
  }

public:
  // returns the stone which corresponds to the
  // specified icon.
  int classify(char __icon) const
  {
    // an icon must either be 'X', 'O', or ' '.
    assert(__icon == 'X' || __icon == 'O' || __icon == ' ');

    return __icon == 'X' ? X : __icon == 'O' ? O : 0;
  }

  // constructor initializes each Tile of the
  // tic-tac-toe board. we also need to ensure that the
  // resulting board configuration is a valid one; this is
  // by ensuring that the number of X's is at most one greater
  // than the number of O's.
  template<class ...Chars>
  Position(Chars&& ...__icons)
  : tiles__ {classify(__icons)...}
  {
    // ensures we only receive only char types as input
    static_assert(TypeCount<char, Chars...> == 9
    , "ONLY ARGUMENTS OF TYPE CHAR CAN BE USED TO INITIALIZE THE POSITION"
              );

    // ensure that the board is completely initialized.
    static_assert(ArgsCount<Chars...> == 9
    , "THE POSITION OBJECT IS NOT COMPLETELY INITIALIZED"
              );

    auto __diff = count(X) - count(O);

    assert((__diff <= 1)
        && (__diff >= 0)
        && "THIS BOARD CONFIGURATION IS NOT VALID");
  }

  // initializes members of the object with
  // their default values.
  Position()
   : Position(' ',' ',' ',' ',' ',' ',' ',' ',' ')
  {}
};

// prints the tic-tac-toe board to the specified output-stream.
inline std::ostream& operator<<(std::ostream& __os, const Position& __pos)
{
  // lambda function returns the icon of the stone
  // on the specified square.
  auto __icon = [&__pos](int __sq)
    {
      return __pos.stone_on(__sq) == X ? 'X'
           : __pos.stone_on(__sq) == O ? 'O' : ' ';
    };

  __os << " "
       << __icon(0)
       << " | "
       << __icon(1)
       << " | "
       << __icon(2)

       << "\n-----------\n "

       << __icon(3)
       << " | "
       << __icon(4)
       << " | "
       << __icon(5)

       << "\n-----------\n "

       << __icon(6)
       << " | "
       << __icon(7)
       << " | "
       << __icon(8)
       << "\n";

  return __os;
}
