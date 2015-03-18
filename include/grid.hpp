#ifndef GRID_H
#define GRID_H


#include <Eigen/Core>

class Grid {
public:
  void Grid(unsigned m_width, unsigned m_height);
  ~void Grid();
  void step();
  MatrixXi getGrid(){ return m_currentCells; };

private:
  const unsigned m_width;
  const unsigned m_height;
  MatrixXi m_currentCells;
  MatrixXi m_nextCells;
  void m_sumNeighbours(unsigned x, unsigned y);

};

void Grid::Grid(unsigned m_width, unsigned m_height){
  currentCells.resize(m_width, m_height);
  nextCells.resize(m_width, m_height);
}

int Grid::m_totalNeighbours(unsigned x, unsigned y){
  int total = 0;

  //repeating boundaries
  if (x != m_width && x != 0){
    total += m_totalNeighbours(x - 1, y);
    total += m_totalNeighbours(x + 1, y);
  }
  else if (x == 0){
    total += m_totalNeighbours(m_width, y);
    total += m_totalNeighbours(x + 1, y);
  }
  else if (x == m_width){
    total += m_totalNeighbours(m_width, y);
    total += m_totalNeighbours(x + 1, y);
  }

  if (y != m_height && y != 0){
    total += m_totalNeighbours(x, y + 1);
    total += m_totalNeighbours(x, y - 1);
  }
  else if (y == 0){
    total += m_totalNeighbours(x, y + 1);
    total += m_totalNeighbours(x, m_height);
  }
  else if (y == m_height){
    y_total += m_totalNeighbours(x, 1);
    total += m_totalNeighbours(x, y - 1);
  }

  return total;
}

void Grid::step(){
  for (unsigned i=0; i < m_width; ++i){
    for (unsigned j=0; j < m_height; ++j){

      //if the cell is alive
      if (m_currentCells(i, j) == 1){

        //underpopulation
        if (m_totalNeighbours(i, j) <= 1){
          m_nextCells(i, j) = 0; //dead
        }
        //overcrowding
        else if (m_totalNeighbours(i, j) == 4){
          m_nextCells(i, j) = 0; //dead
        }
        //survival
        else (){
          m_nextCells(i, j) = 1; //alive
        }
      }
      //or if the cell is dead
      else {
        //reproduction
        if (m_totalNeighbours(i, j) == 3){
          m_nextCells(i, j) = 1; //alive
        }
        else {
          m_nextCells(i, j) = 0; //dead
        }
      }
    }
  }
  m_currentCells = m_nextCells;

}

#endif
