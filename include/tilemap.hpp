//TileMap.hpp
//modified version of example at http://www.sfml-dev.org/tutorials/2.2/graphics-vertex-array.php

#include <Eigen/Core>

class TileMap : public sf::Drawable, public sf::Transformable{
public:

  void TileMap(sf::Vector2u tileSize, unsigned int screenWidth, unsigned int screenHeight);
  void ~TileMap();
  void update();

private:
  unsigned int m_width;
  unsigned int m_height;
  sf::Vector2u m_tileSize;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::VertexArray m_vertices;
};

void TileMap::TileMap(sf::Vector2u tileSize, unsigned int screenWidth, unsigned int screenHeight){

  m_width = screenWidth / tileSize.x;
  m_height = screenHeight / tileSize.y;

  m_tileSize = tileSize;

  // resize the vertex array to fit the level size
  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(m_width * m_height * 4);

}

void TileMap::update(MatrixXi* grid){

  // populate the vertex array, with one quad per tile
  for (unsigned int i = 0; i < m_width; ++i)
    for (unsigned int j = 0; j < m_height; ++j){

      // get a pointer to the current tile's quad
      sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

      // define its 4 corners
      quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
      quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
      quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
      quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);


      if (grid(i, j) == 0){
        //define colors for vertices if dead
        quad[0].color = sf::Color::Black;
        quad[1].color = sf::Color::Black;
        quad[2].color = sf::Color::Black;
        quad[3].color = sf::Color::Black;
      }
      else {
        //define colors for vertices if alive
        quad[0].color = sf::Color::Red;
        quad[1].color = sf::Color::Blue;
        quad[2].color = sf::Color::Green;
        quad[3].color = sf::Color::Yellow;
      }


}


virtual void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  // apply the transform
  states.transform *= getTransform();

  // draw the vertex array
  target.draw(m_vertices, states);
}
