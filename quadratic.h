/**
* \file Header file with quadratic polynomial class declaration.
*
* This file contains the definition of the quadratic polynomial class over the
* field of real numbers.
*/
#pragma once
#include <array>

/// The number of roots obtained by solving the equation.
enum class ERootsFlag {
  RF_NO_ROOTS, ///< Indicates that the equation has no real roots.
  RF_ONE_ROOT, ///< Indicates that an equation has one real root.
  RF_TWO_ROOTS, ///< Indicates that an equation has two real roots.
  RF_INF_ROOTS ///< Indicates that an equation has infinitely real roots.
};

class TQuadPoly {
private:
  double a, b, c; ///< coefficients of the quadratic polynomial: ax^2 + bx + c.

private:
  ERootsFlag quadSolve(std::array<double, 2>& roots) const;

public:
  TQuadPoly(double a, double b, double c);
  
  /**
  * solves the quadratic equation given by the coefficients of the polynomial.
  * 
  * \param [out] roots roots of the solution of the equation.
  * \return value denoting the number of roots
  */
  ERootsFlag solve(std::array<double, 2> &roots) const;
  
  /**
  * method for getting polynomial coefficient values ​​from outside
  * 
  * \return array of three polynomial coefficient values: {a, b, c}
  */
  std::array<double, 3> get() const;
};