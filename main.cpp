#include <cstddef>
#include <iostream>
#include "geom.hpp"
#include "idraw.hpp"
#include "dot.hpp"
#include "canvas.hpp"
#include "lines.hpp"
#include "square.hpp"
#include "rectangle.hpp"


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
