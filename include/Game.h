#ifndef GAME_H
#define GAME_H
/*!
  Author: MaikuZ
*/
#include "Timer.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Bot.h"
using namespace std;
class Game
{
  //!Pl1 <-> 0 is bot, Pl2 <-> 1 is human
  public:
    Game(sf::RenderWindow &app, string fileName = "bot");
    bool makeRound();


    unsigned int widthOfLine = 12;
    unsigned int heightOfTile = 32;
    unsigned int widthOfTile = 32;
    unsigned int round = 0;
    int timeBank = 10000;

    bool isExecutedBot = false;

    vector<sf::Color> playerColor;
    vector<pair<int,int> > Moves = {{0,-1},{0,1},{-1,0},{1,0}};
  protected:

  private:
    void useThreadToMove();
    bool isLegalPosition(int playerID);
    void drawGame();
    void drawGrid();
    void drawCurrentMove();
    BoardMoves oppositeMove(BoardMoves move);

    BoardMoves humanCurrentMove = UP;
    BoardMoves lastHumanMove = UP;
    Timer timer;
    sf::RenderWindow &app;
    Bot bot;

    vector<pair<int,int> > startingPos;
    vector<pair<int,int> > currentPos;
    vector<vector<BoardMoves> > HistoryOfMoves;
    vector<vector<char> > Fields;
};

#endif // GAME_H
