#include <stdexcept>
#include "dot.hpp"


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