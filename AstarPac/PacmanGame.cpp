#include <climits>
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
  m_type parents({ { m_pacman, m_pacman } });

  pq_type frontline(Compare(true));

  std::list<std::pair<int, int>> steps;
  steps.push_back(m_pacman);

  bool** marked = new bool*[m_height];

  int** dist = new int*[m_height];

  for (int i = 0; i<m_height; ++i) {
    marked[i] = new bool[m_width];
    dist[i] = new int[m_width];
    for (int j = 0; j<m_width; ++j) {
      marked[i][j] = false;
      dist[i][j] = INT_MAX;
    }
  }
  marked[m_pacman.first][m_pacman.second] = true;
  dist[m_pacman.first][m_pacman.second] = 0;
  // the starting cell has h(c) only
  frontline.push(std::make_tuple(m_pacman.first, m_pacman.second, abs(m_food.first - m_pacman.first) + abs(m_food.second - m_pacman.second)));

  while (!frontline.empty())
  {
    std::tuple<int, int, int> cur_cell = frontline.top();
    frontline.pop();

    // check if current cell is the food
    if (std::get<0>(cur_cell) == m_food.first && std::get<1>(cur_cell) == m_food.second)
    {
      SetPath(parents);
      break;
    }

    // mark current cell
    marked[std::get<0>(cur_cell)][std::get<1>(cur_cell)] = true;

    std::pair<int, int> adj_cell[4];
    adj_cell[0] = std::make_pair(std::get<0>(cur_cell) - 1, std::get<1>(cur_cell));//up
    adj_cell[1] = std::make_pair(std::get<0>(cur_cell), std::get<1>(cur_cell) - 1);//left
    adj_cell[2] = std::make_pair(std::get<0>(cur_cell), std::get<1>(cur_cell) + 1);//right
    adj_cell[3] = std::make_pair(std::get<0>(cur_cell) + 1, std::get<1>(cur_cell));//down

    for (auto i : adj_cell)
    {
      // ensure neighbor is valid and unmarked
      if (i.first >= 0 && i.first<m_height && i.second >= 0 && i.second<m_width && IsPath((*this)(i.first,i.second)) && !marked[i.first][i.second])
      {
        int newdist = dist[std::get<0>(cur_cell)][std::get<1>(cur_cell)] + (((*this)(i.first,i.second) == SYMBOL_FOOD) ? 0 : 1);

        if (newdist < dist[i.first][i.second])
        {
          //update cost
          dist[i.first][i.second] = newdist;
          parents[i] = std::make_pair(std::get<0>(cur_cell), std::get<1>(cur_cell));

          int heuristic = abs(m_food.first - i.first) + abs(m_food.second - i.second);
          frontline.emplace(std::make_tuple(i.first, i.second, dist[i.first][i.second] + heuristic));
        }
        else
        {
          frontline.emplace(std::make_tuple(i.first, i.second, dist[i.first][i.second]));
        }
      }
    } // end of neighbor cells
  }// end of frontline

  for (int i = 0; i<m_height; ++i) {
    delete marked[i];
    delete dist[i];
  }
  delete marked; delete dist;
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

bool PacmanGame::IsPath(const char c)
{
  return (c == SYMBOL_PATH || c == SYMBOL_FOOD || c == SYMBOL_PACMAN);
}

void PacmanGame::SetPath(m_type & path)
{
  std::pair<int, int> cur_cell(m_food);
  std::pair<int, int> parent_cell(path[m_food]);

  m_steps.push_front(m_food);
  while (parent_cell.first != cur_cell.first || parent_cell.second != cur_cell.second)
  {
    m_steps.push_front(parent_cell);
    cur_cell = parent_cell;
    parent_cell = path[cur_cell];
  }
}
