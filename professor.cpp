#include "professor.h"

void TProfessor::getAnswer(Answer const& ans) {
  this->mail.push(ans);
}

bool checkRoots(Answer const& ans, std::array<double, 2> const& _roots) {
  switch (ans.flag) {
  case ERootsFlag::RF_NO_ROOTS:
    return true;
  case ERootsFlag::RF_ONE_ROOT:
    return ans.roots.at(0) == _roots.at(0);
  case ERootsFlag::RF_TWO_ROOTS:
    return ans.roots.at(0) == _roots.at(0) && ans.roots.at(1) == _roots.at(1);
  case ERootsFlag::RF_INF_ROOTS:
    return true;
  default:
    return false;
  }
}

bool checkAnswer(Answer const& ans) {
  std::array<double, 2> roots;
  ERootsFlag flag = ans.poly.solve(roots);

  if (flag == ans.flag && checkRoots(ans, roots))
    return true;
  return false;
}

void TProfessor::checkAllAnswers() {
  Answer ans(ERootsFlag::RF_NO_ROOTS, {0, 0}, TQuadPoly(0, 0, 0), "");
  while (!mail.empty()) {
    ans = mail.front();
    table[ans.name] += static_cast<int>(checkAnswer(ans));
    mail.pop();
  }
}

void TProfessor::printGradeTable(std::ostream& os) const {
  for (auto student : table)
    os << student.first << "\t" << student.second << std::endl;
}