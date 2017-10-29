#include "Bot.h"
#include <sstream>
#include <iostream>
using namespace std;
Bot::Bot(std::string filename):child(std::string("./" + filename),pstream::pstdin | pstream::pstdout| pstream::pstderr)
{
  child<<"settings player_names player0,player1"<<endl;
  child<<"settings your_bot player0"<<endl;
  child<<"settings timebank 10000"<<endl;
  child<<"settings time_per_move 200"<<endl;
  child<<"settings your_botid 0"<<endl;
  child<<"settings field_width 16"<<endl;
  child<<"settings field_height 16"<<endl;
}
void Bot::updateGameField(vector<vector<char> > &Fields)
{
  string out;
  out = "update game field ";
  for(int i = 0;i < Fields.size();i++)
  {
    for(int j = 0;j < Fields.size();j++)
    {
      char y = Fields[j][i];
      if(y == '.')
      {
        out.push_back('.');
      }
      else if(y == '#')
      {
        out.push_back('x');
      }
      else if(y == 'A')
      {
        out.push_back('0');
      }
      else if(y == 'B')
      {
        out.push_back('1');
      }
      out.push_back(',');
    }
  }
  out.pop_back();
  cout<<out<<endl;
  child<<"update game round "<<round<<endl;
  child<<out<<endl;
}
BoardMoves Bot::getMoveFromBot(int time)
{
  child<<"action move "<<time<<endl;
  char buf[1024];
  std::streamsize n;
  std::string temp;

  while(child >> temp)
  {
    cout<<"Caught " << temp <<" out of the pipe. Now forwarding it..."<<endl;
    if(temp == "left")
    {
      currentMove = LEFT;
    }
    else if(temp == "right")
    {
      currentMove = RIGHT;
    }
    else if(temp == "up")
    {
      currentMove = UP;
    }
    else if(temp == "down")
    {
      currentMove = DOWN;
    }
    else
    {
      cerr<<"INCORRECT INPUT. CLOSING PIPE!"<<endl;
      break;
    }
    round++;
    return currentMove;
  }
  return currentMove;
}
