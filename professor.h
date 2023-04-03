/// \file Header file declaring the professor class and describing the response structure
#pragma once
#include "quadratic.h"
#include <array>
#include <map>
#include <queue>
#include <string>
#include <iostream>

/// the structure of the student's response given by the teacher
struct Answer {
  ERootsFlag flag; ///< the number of roots of the solution
  std::array<double, 2> roots; ///< roots found
  TQuadPoly poly; ///< given polynomial
  std::string name; ///< student name

  Answer(ERootsFlag flag, std::array<double, 2> roots, TQuadPoly poly, std::string name)
    : flag(flag), roots(roots), poly(poly), name(name)
  {}
};

class TProfessor {
private:
  std::queue<Answer> mail; ///< a queue consisting of student responses
  std::map<std::string, int> table; ///< students grade table

public:
  /// getting a response to the queue 
  void getAnswer(Answer const& ans);

  /// ñhecking all responses received and compilation of a student grade table
  void checkAllAnswers();

  /// print of a student grade table
  void printGradeTable(std::ostream& os) const;
};