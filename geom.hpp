#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>
namespace top
{
  struct p_t
  {
    int x, y;
  };

  struct frame_t
  {
    p_t left_bot;
    p_t right_top;
  };

  frame_t build_frame(const p_t*, size_t);

  bool operator==(p_t, p_t);
  bool operator!=(p_t, p_t);

  size_t rows(frame_t);
  size_t cols(frame_t);
  
} // namespace top
#endif // !GEOM_HPP
