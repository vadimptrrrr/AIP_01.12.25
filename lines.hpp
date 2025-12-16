#ifndef LINES_HPP
#define LINES_HPP
#include "geom.hpp"
#include "idraw.hpp"
namespace top
{
  struct Vert_line: IDraw
  {
    Vert_line(int, int, int);
    p_t begin() const override;
    p_t next(p_t) const override;

    private:
    int x;
    int sy;
    int ey;
  };

  struct Hor_line: IDraw
  {
    Hor_line(int, int, int);
    p_t begin() const override;
    p_t next(p_t) const override;

    private:
    int sx;
    int ex;
    int y;
  };

  struct Alfa_line: IDraw
  {
    Alfa_line(p_t, p_t);
    p_t begin() const override;
    p_t next(p_t) const override;

    private:
    p_t start;
    p_t end;
  };
}

#endif // !LINES_HPP