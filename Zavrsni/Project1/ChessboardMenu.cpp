#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "BoardFunctions.h"
#include "Board.h"
#include "Constants.h"
#include "ChessboardMenu.h"


void startMenu()
{
	sf::Window window(sf::VideoMode(800, 600), "Chessboard setup");
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}