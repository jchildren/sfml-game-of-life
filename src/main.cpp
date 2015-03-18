//main.cpp

#include <Eigen/Core>
#include <SFML/Window.hpp>
#include <SFML/Graphics.cpp>

int main {

  const unsigned screenWidth = 800;
  const unsigned screenHeight = 600;

  const unsigned titleSize = 10;

  grid gameOfLife(80, 60);


  sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Also the game");


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

    map.update(gameOfLife.step());

    window.clear();
    window.draw(map);
    // End the current frame and display its contents on screen
    window.display();

  }

  return 0;
}
