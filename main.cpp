#include <SFML/Graphics.hpp>
#include "include/pstream.h"
#include <iostream>
#include "Game.h"
int main()
{

  srand(time(0));
  cout<<"Write the name of your bot executive. It should be in the same folder as this app."<<endl;
  string botName;
  cin>>botName;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  // Create the main window
  sf::RenderWindow app(sf::VideoMode(16*32, 16*32 + 64), "LightRiders", sf::Style::Default, settings);

  while(app.isOpen())
  {
    bool endOfGame = false;
    Game game(app,botName);

    while (app.isOpen())
    {
      // Process events
      sf::Event event;
      while (app.pollEvent(event))
      {
        // Close window : exit
        if (event.type == sf::Event::Closed)
          app.close();
      }


      // Update the window

      if(!endOfGame)
      {
        app.clear();
        if(game.makeRound() == false)
        {
          cout<<"END OF GAME"<<endl;
          endOfGame = true;
        }
        app.display();
      }
      else
      {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
          break;
        sf::sleep(sf::milliseconds(1000/30));
      }
    }
  }

  return EXIT_SUCCESS;
}
