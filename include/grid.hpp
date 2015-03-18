#ifndef GRID_H
#define GRID_H

#include <fstream>
#include <eigen3/Eigen/Core>

class Grid {
public:
  Grid(unsigned, unsigned);
  ~Grid();
  void loadFile();
  MatrixXi step();

private:
  unsigned m_width;
  unsigned m_height;
  MatrixXi m_currentCells;
  MatrixXi m_nextCells;
  void m_sumNeighbours(unsigned, unsigned);

};

Grid::Grid(unsigned width, unsigned height){

  m_width = width;
  m_height = height;

  m_currentCells.resize(m_width, m_height);
  m_nextCells.resize(m_width, m_height);
}

void Grid::loadFile(){

  std::fstream gridFile;

  gridFile.open("startingValues.dat");

  for (unsigned i=0; i < m_width; ++i){
    for (unsigned j=0; j < m_height; ++j){

      gridFile >> m_currentCells(i, j);

    }
  }

  gridFile.close();
}

int Grid::m_sumNeighbours(unsigned x, unsigned y){
  int total = 0;

  //repeating boundaries
  if (x != m_width && x != 0){
    total += m_currentCells(x - 1, y);
    total += m_currentCells(x + 1, y);
  }
  else if (x == 0){
    total += m_currentCells(m_width, y);
    total += m_currentCells(x + 1, y);
  }
  else if (x == m_width){
    total += m_currentCells(m_width, y);
    total += m_currentCells(x + 1, y);
  }

  if (y != m_height && y != 0){
    total += m_currentCells(x, y + 1);
    total += m_currentCells(x, y - 1);
  }
  else if (y == 0){
    total += m_currentCells(x, y + 1);
    total += m_currentCells(x, m_height);
  }
  else if (y == m_height){
    total += m_currentCells(x, 1);
    total += m_currentCells(x, y - 1);
  }

  return total;
}

MatrixXi Grid::step(){
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

  return m_currentCells;

}

#endif
