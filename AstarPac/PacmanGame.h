#pragma once

#define SYMBOL_PACMAN 'P'
#define SYMBOL_FOOD '.'
#define SYMBOL_WALL '%'
#define SYMBOL_PATH '-'
#define CELL_DIM 15

class PacmanGame
{
public:
  PacmanGame(char *mapfile);
  virtual ~PacmanGame();
  void Release();

  void astar();

  int GetWidth() const;
  int GetHeight() const;
  char operator() (int i, int j) const;
  char & operator() (int i, int j);
private:
  int m_width, m_height;
  char *m_grid;
};

