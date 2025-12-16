#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "idraw.hpp"
namespace top
{
  struct Rectangle:IDraw
  {
    Rectangle(p_t pos,int width,int height);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos;
    int w;
    int h;
  };
} // namespace top

#endif // !RECTANGLE_HPP