#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <iosfwd>
#include "geom.hpp"
namespace top
{
  char* build_canvas(frame_t, char);
  void paint_canvas(char*, frame_t, p_t*, char);
  void print_canvas(std::ostream&, char*, frame_t);
} // namespace top


#endif // !CANVAS_HPP