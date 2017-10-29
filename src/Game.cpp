/*!
  Author: MaikuZ
*/
#include "Game.h"
#include <thread>
#include "Timer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Game::Game(sf::RenderWindow &app, string fileName) :
bot(fileName),
Fields(16,vector<char>(16,'.')),
playerColor({sf::Color::Blue,sf::Color::Red}),
startingPos({{0,0},{0,0}}),
HistoryOfMoves(2),
app(app)
{
 //Getting a random position for first player. The other one has symmetrical position.
 startingPos[0] = make_pair(rand()%16,rand()%16);
 startingPos[1] = make_pair((16-1) - startingPos[0].first,startingPos[0].second);

 if(rand()%2 == 0)
  swap(startingPos[0],startingPos[1]);

 Fields[startingPos[0].first][startingPos[0].second] = 'A';
 Fields[startingPos[1].first][startingPos[1].second] = 'B';

 currentPos = startingPos;

}
void Game::useThreadToMove()
{
  bot.round = round;
  bot.updateGameField(Fields);
  bot.getMoveFromBot(timeBank);
}

void Game::drawCurrentMove()
{
  sf::Color currentColor = sf::Color::Cyan;
  sf::CircleShape joint(widthOfLine/2);
  joint.setFillColor(currentColor);

  pair<int,int> currentPosition = currentPos[1];

  pair<int,int> newPosition =
  {currentPosition.first + Moves[humanCurrentMove].first,
  currentPosition.second + Moves[humanCurrentMove].second};

  joint.setPosition(newPosition.first * 32 + 16 - widthOfLine/2, newPosition.second * 32 + 16 - widthOfLine/2);
  app.draw(joint);
}

bool Game::makeRound()
{
  cout<<"Round "<<round<<endl;

  /*
  cout<<currentPos[0].first<<" : "<<currentPos[0].second<<endl;
  cout<<currentPos[1].first<<" : "<<currentPos[1].second<<endl;
  */

  timeBank = min(10000,timeBank + 200);
  timer.startTimer();


  drawGrid();
  drawGame();
  app.display();

  sf::Thread makeMoveThread(&Game::useThreadToMove,this);
  makeMoveThread.launch();

  vector<sf::Keyboard::Key> Keys ({sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right});

  while(bot.round == round and timer.endTimer() < timeBank)
  {
    for(int i = 0;i < Keys.size();i++)
    {
      if(sf::Keyboard::isKeyPressed(Keys[i]))
      {
        ///Only when round 0 allow opposite direction moves...
        if(round == 0 or lastHumanMove != oppositeMove((BoardMoves)(i)))
          humanCurrentMove = (BoardMoves)(i);
      }
    }

    app.clear();
    drawGrid();
    drawGame();
    drawCurrentMove();
    app.display();

    ///use sleep to avoid overusing CPU
    sf::sleep(sf::milliseconds(10));
  }

  timeBank -= timer.endTimer();

  if(bot.round == round)
    cout<<"Bot timed out... Going forwards."<<endl;
  cout<<"Bot was thinking for " <<timer.endTimer()<<" ms"<<endl;
  cout<<"TimeBank "<<timeBank<<endl;

  timeBank = max(0,timeBank);

  while(timer.endTimer() < 1000)
  {
    for(int i = 0;i < Keys.size();i++)
    {
      if(sf::Keyboard::isKeyPressed(Keys[i]))
      {
        ///Only when round 0 allow opposite direction moves...
        if(round == 0 or lastHumanMove != oppositeMove((BoardMoves)(i)))
          humanCurrentMove = (BoardMoves)(i);
      }
    }

    app.clear();
    drawGrid();
    drawGame();
    drawCurrentMove();
    app.display();

    sf::sleep(sf::milliseconds(1000/30));///Basically ~30 fps
  }
  makeMoveThread.terminate();
  round++;

  HistoryOfMoves[0].push_back(bot.currentMove);
  HistoryOfMoves[1].push_back(humanCurrentMove);

  ///Last player positions become wall
  Fields[currentPos[0].first][currentPos[0].second] = '#';
  Fields[currentPos[1].first][currentPos[1].second] = '#';

  currentPos[0].first += Moves[bot.currentMove].first;
  currentPos[0].second += Moves[bot.currentMove].second;


  currentPos[1].first += Moves[humanCurrentMove].first;
  currentPos[1].second += Moves[humanCurrentMove].second;



  if(!isLegalPosition(0) and !isLegalPosition(1))
  {
    cout<<"DRAW"<<endl;
    return false;
  }
  if(!isLegalPosition(1))
  {
    cout<<"BOT WINS!"<<endl;
    return false;
  }
  if(!isLegalPosition(0))
  {
    cout<<"Player WINS!"<<endl;
    return false;
  }

  Fields[currentPos[0].first][currentPos[0].second] = 'A';
  Fields[currentPos[1].first][currentPos[1].second] = 'B';
  lastHumanMove = humanCurrentMove;
  cout<<endl<<endl<<endl;
  return true;
}


bool Game::isLegalPosition(int playerID)
{

  if(currentPos[playerID].first < 0 or currentPos[playerID].second < 0)
    return false;

  if(currentPos[playerID].first > 15 or currentPos[playerID].second > 15)
    return false;

  if(Fields[currentPos[playerID].first][currentPos[playerID].second] == '#')
    return false;

  return true;
}



void Game::drawGame()
{
  for(int playerID = 0;playerID < 2;playerID++)
  {
    sf::Color currentColor = playerColor[playerID];
    sf::RectangleShape line(sf::Vector2f(32,widthOfLine));
    line.setFillColor(currentColor);

    pair<int,int> currentPosition = startingPos[playerID];

    sf::CircleShape joint(widthOfLine/2);
    joint.setFillColor(currentColor);
    joint.setPosition(currentPosition.first * 32 + 16 - widthOfLine/2, currentPosition.second * 32 + 16 - widthOfLine/2);
    app.draw(joint);

    for(auto x: HistoryOfMoves[playerID])
    {
      joint.setFillColor(currentColor);
      joint.setPosition(currentPosition.first * 32 + 16 - widthOfLine/2, currentPosition.second * 32 + 16 - widthOfLine/2);

      pair<int,int> newPosition = {currentPosition.first + Moves[(int)x].first,currentPosition.second + Moves[(int)x].second};
      sf::Vector2f sizeOfLine;
      sf::Vector2f positionOfLine;

      switch (x)
      {
      case UP:
        sizeOfLine = {widthOfLine,32};
        positionOfLine = {currentPosition.first * 32 + 16 - widthOfLine/2, (currentPosition.second-1)  * 32 + 16};
        break;
      case DOWN:
        sizeOfLine = {widthOfLine,32};
        positionOfLine = {newPosition.first * 32 + 16 - widthOfLine/2, (newPosition.second - 1) * 32 + 16};
        break;
      case LEFT:
        sizeOfLine = {32,widthOfLine};
        positionOfLine = {newPosition.first * 32 + 16, (newPosition.second) * 32 + 16 - widthOfLine/2};
        break;
      case RIGHT:
        sizeOfLine = {32,widthOfLine};
        positionOfLine = {currentPosition.first * 32 + 16, (currentPosition.second) * 32 + 16 - widthOfLine/2};
        break;
      }

      line.setSize(sizeOfLine);
      line.setPosition(positionOfLine);
      app.draw(line);
      app.draw(joint);

      currentPosition = newPosition;

    }
  }
}


void Game::drawGrid()
{
  sf::RectangleShape line(sf::Vector2f(16*32,2));
  line.setFillColor(sf::Color(128,128,128));//Grey
  for(int j = 0;j < 2;j++)
  {
    for(int i = 0;i <= 16;i++)
    {
      line.setRotation(j*90);
      if(j == 0)
        line.setPosition(0,i*32);
      else
        line.setPosition(i*32,0);
      app.draw(line);
    }
  }
}



BoardMoves Game::oppositeMove(BoardMoves move)
{
  switch (move)
  {
  case UP:
    return DOWN;
    break;
  case DOWN:
    return UP;
    break;
  case LEFT:
    return RIGHT;
    break;
  case RIGHT:
    return LEFT;
    break;
  }
}
