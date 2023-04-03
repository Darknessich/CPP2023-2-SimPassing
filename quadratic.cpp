#include "quadratic.h"
#include <cmath>

TQuadPoly::TQuadPoly(double a, double b, double c)
  : a(a), b(b), c(c)
{
}

ERootsFlag TQuadPoly::quadSolve(std::array<double, 2>& _roots) const {
  ERootsFlag result = ERootsFlag::RF_NO_ROOTS;
  double bNew = b / (2.0 * a);
  double cNew = bNew * bNew - c / a;

  if (cNew > 0.0) {
    result = ERootsFlag::RF_TWO_ROOTS;
    _roots.at(0) = -bNew - std::sqrt(cNew);
    _roots.at(1) = -bNew + std::sqrt(cNew);
  }
  else if (cNew == 0.0) {
    result = ERootsFlag::RF_ONE_ROOT;
    _roots.at(0) = -bNew;
  }

  return result;
}

ERootsFlag TQuadPoly::solve(std::array<double, 2>& _roots) const {
  ERootsFlag result;

  if (a == 0.0 && b == 0.0) {
    result = (c == 0.0) ? ERootsFlag::RF_INF_ROOTS : ERootsFlag::RF_NO_ROOTS;
  }
  else if (a == 0.0) {
    result = ERootsFlag::RF_ONE_ROOT;
    _roots.at(0) = - c / b;
  }
  else {
    result = quadSolve(_roots);
  }

  return result;
}