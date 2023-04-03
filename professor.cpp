#include "professor.h"

TAnswer::TAnswer()
  : flag(ERootsFlag::RF_NO_ROOTS), roots({ 0, 0 }), poly(0, 0, 0), name("")
{}

TAnswer::TAnswer(ERootsFlag flag, std::array<double, 2> roots, TQuadPoly poly, std::string name)
  : flag(flag), roots(roots), poly(poly), name(name)
{}

bool TAnswer::isCorrect() const {
  std::array<double, 2> correctRoots;
  ERootsFlag correctFlag = this->poly.solve(correctRoots);

  if (this->flag != correctFlag)
    return false;

  switch (this->flag) {
  case ERootsFlag::RF_NO_ROOTS:
    return true;
  case ERootsFlag::RF_ONE_ROOT:
    return this->roots.at(0) == correctRoots.at(0);
  case ERootsFlag::RF_TWO_ROOTS:
    return this->roots.at(0) == correctRoots.at(0) && this->roots.at(1) == correctRoots.at(1);
  case ERootsFlag::RF_INF_ROOTS:
    return true;
  default:
    return false;
  }
}

void TProfessor::getAnswer(TAnswer const& ans) {
  this->mail.push(ans);
}

void TProfessor::checkAllAnswers() {
  TAnswer ans;
  while (!mail.empty()) {
    ans = mail.front();
    table[ans.name] += static_cast<int>(ans.isCorrect());
    mail.pop();
  }
}

void TProfessor::printGradeTable(std::ostream& os) const {
  for (auto student : table)
    os << student.first << "\t" << student.second << std::endl;
}