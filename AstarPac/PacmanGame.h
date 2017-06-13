#pragma once
#include <list>
#include <tuple>
#include <map>
#include <queue>
#include <utility>

#define SYMBOL_PACMAN 'P'
#define SYMBOL_FOOD '.'
#define SYMBOL_WALL '%'
#define SYMBOL_PATH '-'

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
  std::pair<int, int> m_pacman;
  std::pair<int, int> m_food;
  std::list<std::pair<int,int>> m_steps;
  bool IsPath(const char c);
  void SetPath(m_type &path);
};

class Compare {
  bool reverse;
public:
  Compare(const bool& rev = false) { reverse = rev; }
  bool operator() (const std::tuple<int, int, int>& ls, const std::tuple<int, int, int>& rs) const
  {
    if (reverse)
      return std::get<2>(ls) > std::get<2>(rs);
    else
      return std::get<2>(ls) < std::get<2>(rs);
  }
};

typedef std::map<std::pair<int, int>, std::pair<int, int>> m_type;
typedef std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, Compare> pq_type;
