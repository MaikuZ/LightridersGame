LightridersGame

This software relies on PStreams(http://pstreams.sourceforge.net/, BOOST license, include/pstreams.h file) and SFML library(https://www.sfml-dev.org/, zlib/png license, library used for 2d graphics) and blaavogn's starter bot(https://github.com/blaavogn/light-riders-starterbot/, only include/GameEnums.h). 

This software is a Lightriders game environment from https://starapple.riddles.io/competitions/light-riders.
It is designed to offer a human player the possibility to fight against his or someone else's bot. 


Picture presenting the environment.

![alt text](https://github.com/MaikuZ/LightridersGame/blob/master/lightridersGame.jpeg)

HOW TO USE

To use this software one has to compile it first using make. The binary will be created in bin directory.

(I haven’t tested it on Windows yet)

Once compiled please put the ligthridersGame executive file in the same directory as your bot executive file.
You can then execute lightridersGame(through console). If you execute it in console/terminal it will prompt you to write your bot's executive file name. Once you type it in and press enter the game will start. 

HOW TO PLAY

You play against your bot using arrows. Each turn you will have at least 1 second time for your decision(you have to wait for the enemy bot to stop thinking and output his move, if he thinks for more than 10 seconds his moves will always be forwards). The cyan dot shows your current direction. Your colour is red. 

GAME MECHANICS

Game mechanics are exactly the same as in https://starapple.riddles.io/competitions/light-riders/how-to-play

After the game ends you may press R button and the game will restart with new random starting positions.
