//main.cpp

#include <Eigen/Core>
#include <SFML/Window.hpp>
#include <SFML/Graphics.cpp>

int main {

  const unsigned screen_width = 800;
  const unsigned screen_height = 600;

  const unsigned title_size = 10;




  sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Also the game");

  // create a 500x500 render-texture
  sf::RenderTexture renderTexture;
  if (!renderTexture.create(screen_width, screen_height))
  {
    // error...
  }

  // run the program as long as the window is open
  while (window.isOpen()){
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)){
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // clear the window with white color
    renderTexture.clear(sf::Color::White);

    // draw everything here...
    // window.draw(...);

    // end the current frame
    renderTexture.display();

    // Draw the texture
    sf::Sprite sprite(renderTexture.getTexture());
    window.draw(sprite);
    // End the current frame and display its contents on screen
    window.display();

  }

  return 0;
}