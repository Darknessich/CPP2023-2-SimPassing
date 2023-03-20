#pragma once
#include <iostream>
#include <array>
#include <string>
#include <queue>
#include <map>
#include "Quadratic.h"

struct Answer {
  rootsFlag flag;
  std::array<double, 2> roots;
  std::array<double, 3> poly;
  std::string name;
};

class Professor {
public:
  void getAnswer(Answer const& ans);
  void checkAllAnswers();
  void createGradeTable(std::ostream& os) const;
private:
  bool checkAnswer(Answer const& ans) const;
  std::queue<Answer> mail;
  std::map<std::string, int> table;
};