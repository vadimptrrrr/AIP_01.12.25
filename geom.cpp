#include <stdexcept>
#include "geom.hpp"
bool top::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool top::operator!=(p_t a, p_t b)
{
  return !(a == b);
}

size_t top::rows(frame_t f)
{
  return f.right_top.y - f.left_bot.y + 1;
}

size_t top::cols(frame_t f)
{
  return f.right_top.x - f.left_bot.x + 1;
}

top::frame_t top::build_frame(const p_t* ps, size_t s)
{
  if(!s)
  {
    throw std::logic_error("bad size");
  }

  int minx = ps[0].x, miny = ps[0].y,
  maxx = ps[0].x, maxy = ps[0].y;

  for (size_t i = 1; i < s; ++i)
  {
    minx = (ps[i].x < minx)? ps[i].x : minx;
    maxx = (ps[i].x > maxx)? ps[i].x : maxx;
    miny = (ps[i].y < miny)? ps[i].y : miny;
    maxy = (ps[i].y > maxy)? ps[i].y : maxy;
  }
  top::p_t aa{minx, miny};
  top::p_t bb{maxx, maxy};
  top::frame_t ans = {aa, bb};
  return ans;
}