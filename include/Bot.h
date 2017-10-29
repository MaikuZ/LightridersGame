#ifndef BOT_H
#define BOT_H
/*!
  Author: MaikuZ
*/
#include "pstream.h"
#include "GameEnums.h"
#include <string>
#include <vector>
using namespace redi;
using namespace std;
class Bot
{
  public:
    Bot(std::string fileName = "bot");
    int round = 0;
    BoardMoves currentMove = UP;
    pstream child;
    void updateGameField(vector<vector<char> > &Fields);
    BoardMoves getMoveFromBot(int time);
  protected:

  private:
};

#endif // BOT_H
