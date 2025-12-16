#include "square.hpp"

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