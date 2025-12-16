#include <iostream>
#include "canvas.hpp"

char* top::build_canvas(frame_t f, char fill)
{
  size_t size = rows(f) * cols(f);
  char* n = new char[size];
  for(size_t i = 0; i < size; ++i)
  {
    n[i] = fill;
  }
  return n;
}

void top::paint_canvas(char* cnv, frame_t fr, p_t* p, char f)
{
  int dx = p->x - fr.left_bot.x;
  int dy = fr.right_top.y - p->y;
  cnv[dy * cols(fr) + dx] = f;
}

void top::print_canvas(std::ostream& os, char* cnv, frame_t fr)
{
  for(size_t i = 0; i < rows(fr); ++i)
  {
    for(size_t j = 0; j < cols(fr); ++j)
    {
      os << cnv[i * cols(fr) + j];
    }
    os << "\n";
  }
}