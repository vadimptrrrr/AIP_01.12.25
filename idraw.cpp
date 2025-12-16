#include "idraw.hpp"

namespase
{
  void extend(top::p_t** pts, size_t s, top::p_t p)
  {
    size_t upd_s = s + 1;
    top::p_t* res = new top::p_t[upd_s];
    for (size_t i = 0; i < s; ++i)
    {
      res[i] = (*pts)[i];
    }
    res[s] = p;
    delete[] *pts;
    *pts = res;
  }
} // namespase anonim

size_t top::get_points(IDraw* b, p_t** ps, size_t s)
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
