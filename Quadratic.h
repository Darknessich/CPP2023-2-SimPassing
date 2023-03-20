#pragma once
#include <array>

enum class rootsFlag {
  NO_ROOTS,
  ONE_ROOT,
  TWO_ROOTS,
  INF_ROOTS
};

rootsFlag Solve(std::array<double, 3> const& _poly, std::array<double, 2>& _roots);
