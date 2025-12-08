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

  void make_f(IDraw** b, size_t k)
  {

  }

  size_t rows(frame_t f)
  {
    return f.right_top.y - f.left_bot.y + 1;
  }

  size_t cols(frame_t f)
  {
    return f.right_top.x - f.left_bot.x + 1;
  }

  size_t get_points(IDraw* b, p_t** ps, size_t s)
  {
    size_t k = 1;

    p_t start = b->begin();
    p_t next = b->next(start);
    while(start != next)
    {
      ++k;
      start = next;
      next = b->next(start);
    }

    p_t* arr_p = new p_t[s + k];

    for(size_t i = 0; i < s; ++i)
    {
      arr_p[i] = *ps[i];
    }
    arr_p[s] = (b->begin());
    for(size_t i = 1; i < k; ++i)
    {
      arr_p[s+i] = b->next(arr_p[s+i-1]);
    }

    delete[] *ps;
    *ps = arr_p;
    s += k;
    return s;
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

  void paint_canvas(char* cnv, frame_t fr, const p_t* ps, size_t k, char f)
  {

  }

  void print_canvas(const char* cnv, frame_t fr)
  {

  }
}


int main()
{
  using namespace top;
  int err = 0;
  IDraw* f[3] = {};
  char* cnv = nullptr;
  p_t* p = nullptr;
  p_t** kp = nullptr;

  try
  {
    make_f(f, 3);
    size_t s = 0;
    for(size_t i =0; i < 3; ++i)
    {
      get_points(f[i], kp, s);
    }
    frame_t fr = build_frame(p, s);
    cnv = build_canvas(fr, '.');
    paint_canvas(cnv, fr, p, s, '#');
    print_canvas(cnv, fr);
  } catch (...) {
    err = 1;
    delete f[0];
    delete f[1];
    delete f[2];
    delete[] p;
    delete[] cnv;
    return err;
  }
}

top::Dot::Dot(int x, int y):
  IDraw(),
  d{x, y}
{}

top::Dot::Dot(p_t p):
  IDraw(),
  d{p}
{}

top::p_t top::Dot::begin() const{
  return d;
}
top::p_t top::Dot::next(p_t prev) const{
  if (prev != begin()) {
    throw std::logic_error("bad impl");
  }
  return d;
}