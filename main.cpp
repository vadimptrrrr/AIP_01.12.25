#include <cstddef>
#include <iostream>

namespace top
{
  struct p_t
  {
    int x, y;
  };

  struct IDraw
  {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  struct Dot: IDraw
  {
    Dot(int x, int y);
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t d;
  };

  struct Vert_line: IDraw
  {
    Vert_line(int x, int starty, int endy);
    p_t begin() const override;
    p_t next(p_t) const override;

    private:
    int x;
    int sy;
    int ey;
  };

  struct Hor_line: IDraw
  {
    Hor_line(int sx, int endx, int y);
    p_t begin() const override;
    p_t next(p_t) const override;

    private:
    int sx;
    int ex;
    int y;
  };

  struct Alfa_line: IDraw
  {
    Alfa_line(p_t a, p_t b);
    p_t begin() const override;
    p_t next(p_t) const override;

    private:
    p_t start;
    p_t end;
  };

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

  struct frame_t
  {
    p_t left_bot;
    p_t right_top;
  };

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }

  size_t rows(frame_t f)
  {
    return f.right_top.y - f.left_bot.y + 1;
  }

  size_t cols(frame_t f)
  {
    return f.right_top.x - f.left_bot.x + 1;
  }

    void extend(p_t** pts, size_t s, p_t p)
  {
    size_t upd_s = s + 1;
    p_t* res = new p_t[upd_s];
    for (size_t i = 0; i < s; ++i)
    {
      res[i] = (*pts)[i];
    }
    res[s] = p;
    delete[] *pts;
    *pts = res;
  }

  size_t get_points(IDraw* b, p_t** ps, size_t s)
  {
    p_t p = b->begin();
    extend(ps, s, p);
    size_t delta = 1;
    while (b->next(p) != b->begin())
    {
      p = b->next(p);
      extend(ps, s + delta, p);
      ++delta;
    }
    return delta;
  }

  frame_t build_frame(const p_t* ps, size_t s)
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
    p_t aa{minx, miny};
    p_t bb{maxx, maxy};
    frame_t ans = {aa, bb};
    return ans;
  }

  char* build_canvas(frame_t f, char fill)
  {
    size_t size = rows(f) * cols(f);
    char* n = new char[size];
    for(size_t i = 0; i < size; ++i)
    {
      n[i] = fill;
    }
    return n;
  }

  void paint_canvas(char* cnv, frame_t fr, p_t* p, char f)
  {
    int dx = p->x - fr.left_bot.x;
    int dy = fr.right_top.y - p->y;
    cnv[dy * cols(fr) + dx] = f;
  }

  void print_canvas(std::ostream& os, char* cnv, frame_t fr)
  {
    for(size_t i = 0; i < rows(fr); ++i)
    {
      for(size_t j = 0; j < cols(fr); ++j)
      {
        os << cnv[i * cols(fr) + j];
      }
      os << "\n";
    }
  }
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

top::Dot::Dot(int x, int y):
  IDraw(),
  d{x, y}
{}

top::Dot::Dot(p_t p):
  IDraw(),
  d{p}
{}

top::p_t top::Dot::begin() const
{
  return d;
}
top::p_t top::Dot::next(p_t prev) const
{
  if (prev != begin()) {
    throw std::logic_error("bad impl");
  }
  return d;
}

top::Vert_line::Vert_line(int xx, int syy, int eyy):
  IDraw(),
  x{xx}, sy{syy}, ey{eyy}
{}

top::p_t top::Vert_line::begin() const
{
  return {x, sy};
}

top::p_t top::Vert_line::next(p_t p) const
{
  p_t end = {x, ey};
  if (p == end)
  {
    return begin();
  }
  return {p.x, p.y + 1};
}

top::Hor_line::Hor_line(int sxx, int exx, int yy):
  IDraw(),
  sx{sxx}, ex{exx}, y{yy}
{}

top::p_t top::Hor_line::begin() const
{
  return {sx, y};
}

top::p_t top::Hor_line::next(p_t p) const
{
  p_t end = {ex, y};
  if (p == end)
  {
    return begin();
  }
  return {p.x + 1, y};
}

top::Alfa_line::Alfa_line(p_t aa, p_t bb):
  IDraw(),
  start{aa}, end{bb}
{}

top::p_t top::Alfa_line::begin() const
{
  return start;
}

top::p_t top::Alfa_line::next(p_t p) const
{
  if (p == end)
  {
    return begin();
  }
  return {p.x + 1, p.y + 1};
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