#include "stdafx.h"
#include "PacmanGame.h"


PacmanGame::PacmanGame(char * mapfile)
{
  std::ifstream inf(mapfile, std::ifstream::in);
  if (!inf)
  {
    exit(1);
  }

  inf >> m_height >> m_width;

  m_grid = new char[m_height*m_width];

  for (int i = 0; i < m_height; ++i)
  {
    for (int j = 0; j < m_width; ++j)
    {
      inf >> (*this)(i, j);
    }
  }

  inf.close();
}

PacmanGame::~PacmanGame()
{
  delete[] m_grid;
}

void PacmanGame::Release()
{
  delete[] m_grid;
  m_height = 0;
  m_width = 0;
}


void PacmanGame::astar()
{
}

int PacmanGame::GetWidth() const
{
  return m_width;
}

int PacmanGame::GetHeight() const
{
  return m_height;
}

char PacmanGame::operator()(int i, int j) const
{
  assert(i >= 0 && i <= m_height && j >= 0 && j <= m_width);

  return m_grid[i * m_width + j];
}

char & PacmanGame::operator()(int i, int j)
{
  assert(i >= 0 && i <= m_height && j >= 0 && j <= m_width);

  return m_grid[i * m_width + j];
}
