#include "Quadratic.h"
#include <cmath>

rootsFlag QuadraticSolve(std::array<double, 3> const & _poly, std::array<double, 2>& _roots) {
  rootsFlag result = rootsFlag::NO_ROOTS;
  double b = _poly.at(1) / (2.0 * _poly.at(0));
  double c = b * b - _poly.at(2) / _poly.at(0);

  if (c > 0.0) {
    result = rootsFlag::TWO_ROOTS;
    _roots.at(0) = -b - std::sqrt(c);
    _roots.at(1) = -b + std::sqrt(c);
  }
  else if (c == 0.0) {
    result = rootsFlag::ONE_ROOT;
    _roots.at(0) = -b;
  }

  return result;
}

rootsFlag Solve(std::array<double, 3> const& _poly, std::array<double, 2>& _roots) {
  rootsFlag result;

  if (_poly.at(0) == 0.0 && _poly.at(1) == 0.0) {
    result = (_poly.at(2) == 0.0) ? rootsFlag::INF_ROOTS : rootsFlag::NO_ROOTS;
  }
  else if (_poly.at(0) == 0.0) {
    result = rootsFlag::ONE_ROOT;
    _roots.at(0) = - _poly.at(2) / _poly.at(1);
  }
  else {
    result = QuadraticSolve(_poly, _roots);
  }

  return result;
}