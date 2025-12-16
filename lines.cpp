#include "lines.hpp"
#include "geom.hpp"

top::Vert_line::Vert_line(int xx, int syy, int eyy):
  IDraw(),
  x{xx}, sy{syy}, ey{eyy}
{}

top::p_t top::Vert_line::begin() const
{
  return {x, sy};
}

top::p_t top::Vert_line::next(p_t p) const
{
  p_t end = {x, ey};
  if (p == end)
  {
    return begin();
  }
  return {p.x, p.y + 1};
}

top::Hor_line::Hor_line(int sxx, int exx, int yy):
  IDraw(),
  sx{sxx}, ex{exx}, y{yy}
{}

top::p_t top::Hor_line::begin() const
{
  return {sx, y};
}

top::p_t top::Hor_line::next(p_t p) const
{
  p_t end = {ex, y};
  if (p == end)
  {
    return begin();
  }
  return {p.x + 1, y};
}

top::Alfa_line::Alfa_line(p_t aa, p_t bb):
  IDraw(),
  start{aa}, end{bb}
{}

top::p_t top::Alfa_line::begin() const
{
  return start;
}

top::p_t top::Alfa_line::next(p_t p) const
{
  if (p == end)
  {
    return begin();
  }
  return {p.x + 1, p.y + 1};
}