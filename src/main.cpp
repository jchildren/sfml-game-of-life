//main.cpp

#include <iostream>
#include <eigen3/Eigen/Core>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "tilemap.hpp"

const unsigned screenWidth = 300;
const unsigned screenHeight = 200;

const unsigned tileSize = 100;

int main() {

  Grid gameOfLife(3, 2);

  sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Also the game");

  TileMap map(sf::Vector2u(tileSize, tileSize), screenWidth, screenHeight);

  // run the program as long as the window is open
  while (window.isOpen()){
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)){
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    //map.update(gameOfLife.step());

    window.clear();
    window.draw(map);
    // End the current frame and display its contents on screen
    window.display();

  }

  return 0;
}
