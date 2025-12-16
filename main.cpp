#include <cstddef>
#include <iostream>
#include "geom.hpp"
#include "idraw.hpp"
#include "dot.hpp"
#include "canvas.hpp"
#include "lines.hpp"

namespace top
{
  struct Square:IDraw
  {
    Square(p_t pos,int width);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos;
    int w;
  };

  struct Rectangle:IDraw
  {
    Rectangle(p_t pos,int width,int height);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos;
    int w;
    int h;
  };
}


int main()
{
  using namespace top;
  int err = 0;
  IDraw* f[6] = {};
  p_t * pts = nullptr;
  size_t s = 0;

  try
  {
    f[0] = new Dot(0, 0);
    f[1] = new Vert_line(5, -3, 3);
    f[2] = new Hor_line(-5, 0, -2);
    f[3] = new Alfa_line({-3, 3}, {6, 12});
    f[4] = new Square({6, 6}, 3);
    f[5] = new Rectangle({-6, -6}, 2, 3);
    for(size_t i = 0; i < 6; ++i)
    {
      s += get_points((f[i]), &pts, s);
    }
    frame_t fr = build_frame(pts, s);
    char* cnv = build_canvas(fr, '.');
    for (size_t i = 0; i < s; ++i)
    {
      paint_canvas(cnv, fr, pts + i, '#');
    }
    print_canvas(std::cout, cnv, fr);
  } catch (...) {
    err = 2;
    std::cerr << "Bad drawing\n";
  }
  err = 1;
  delete f[0];
  delete f[1];
  delete f[2];
  delete f[3];
  delete f[4];
  delete f[5];
  delete[] pts;
  return err;
}

top::Square::Square(p_t pos,int width):
  pos(pos),
  w(width)
{}

top::p_t top::Square::begin() const {
  return pos;
}

top::p_t top::Square::next(p_t prev) const {

  if (prev.x==pos.x && prev.y>pos.y)
  {
    return {prev.x,prev.y-1};
  }
  else if (prev.x==pos.x+w-1 && prev.y<pos.y+w-1)
  {
    return {prev.x,prev.y+1};
  }
  else if (prev.y==pos.y+w-1 && prev.x>pos.x)
  {
    return {prev.x-1,prev.y};
  }
  else if (prev.y==pos.y && prev.x<pos.x+w-1)
  {
    return {prev.x+1,prev.y};
  }
  return pos;
}

top::Rectangle::Rectangle(p_t pos,int width,int height):
  pos(pos),
  w(width),
  h(height)
{}

top::p_t top::Rectangle::begin() const {
  return pos;
}

top::p_t top::Rectangle::next(p_t prev) const
{
  if (prev.x==pos.x && prev.y>pos.y)
  {
    return {prev.x,prev.y-1};
  }
  else if (prev.x==pos.x+w-1 && prev.y<pos.y+h-1)
  {
    return {prev.x,prev.y+1};
  }
  else if (prev.y==pos.y+h-1 && prev.x>pos.x)
  {
    return {prev.x-1,prev.y};
  }
  else if (prev.y==pos.y && prev.x<pos.x+w-1)
  {
    return {prev.x+1,prev.y};
  }
  return pos;
}