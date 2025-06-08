#include <array>
#include <cassert>
#include <algorithm>

#include "position.hpp"
#include "movegen.hpp"
#include "search.hpp"

int play_game(bool XisAi)
{
  puts("NEW GAME!\n");

  Position pos;
  bool ai_turn = XisAi;

  std::cout << pos;

  while (!pos.terminal())
  {
    if (ai_turn)
    {
      auto sq = NegaMax(pos).search();
      pos.make_move(sq);
      std::cout << "Computer Move: " << sq << std::endl;
      std::cout << std::endl << pos;
    }
    else
    {
      MoveGen mlist__(pos);

      int sq=9;

      do {

        std::cout << "Enter Your Move[1-9]: ";

        sq = getchar() - '1';
        getchar(); // read 'ENTER'

        if (!isdigit(sq+'1'))
        {
          return 0;
        }
      } while (!mlist__.count(sq));

      pos.make_move(sq);
    }
    ai_turn = !ai_turn;
  }

  std::cout << std::endl;

  if (ai_turn) std::cout << pos;

  if (!pos.winner())
  {
    puts("IT'S A DRAW!");
  }
  // unless handicapped, it is theoretically and practically
  // impossible for computer to loose a game.
  else if ((pos.winner() == 1 && !XisAi)
        || (pos.winner() == -1 && XisAi))
  {
    puts("YOU WIN!");
  }
  else if ((pos.winner() == -1 && !XisAi)
        || (pos.winner() == 1 && XisAi))
  {
    puts("YOU LOOSE!");
  }

  std::cout << std::endl;

  return 1;
}

int main()
{
  for (int i=0; play_game(i%2); i++);
}
