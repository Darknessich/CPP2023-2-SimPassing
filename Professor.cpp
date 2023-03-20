#include "Professor.h"

void Professor::getAnswer(Answer const& ans) {
  this->mail.push(ans);
}

bool checkRoots(Answer const& ans, std::array<double, 2> const& _roots) {
  switch (ans.flag) {
  case rootsFlag::NO_ROOTS: 
    return true;
  case rootsFlag::ONE_ROOT:
    return ans.roots.at(0) == _roots.at(0);
  case rootsFlag::TWO_ROOTS:
    return ans.roots.at(0) == _roots.at(0) && ans.roots.at(1) == _roots.at(1);
  case rootsFlag::INF_ROOTS:
    return true;
  default:
    return false;
  }
}

bool Professor::checkAnswer(Answer const& ans) const {
  std::array<double, 2> roots;
  rootsFlag flag = Solve(ans.poly, roots);

  if (flag == ans.flag && checkRoots(ans, roots))
    return true;
  return false;
}

void Professor::checkAllAnswers() {
  Answer ans;
  while (!mail.empty()) {
    ans = mail.front();
    table[ans.name] += static_cast<int> (this->checkAnswer(ans));
    mail.pop();
  }
}

void Professor::createGradeTable(std::ostream& os) const {
  for (auto student : table)
    os << student.first << "\t" << student.second << std::endl;
}