#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "geom.hpp"
#include "idraw.hpp"

namespace top
{
  struct Square:IDraw
  {
    Square(p_t, int);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos;
    int w;
  };
} // namespace top

#endif // !SQUARE_HPP