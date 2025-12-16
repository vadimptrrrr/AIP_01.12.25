#ifndef IDRAW_HPP
#define IDRAW_HPP
#include "geom.hpp"

namespace top
{
  struct IDraw
  {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  size_t get_points(IDraw*, p_t**, size_t);
} // namespace top


#endif // !IDRAW_HPP