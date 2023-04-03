#include "student.h"
#include <random>

bool isFail() {
  // Probability of an normal student's error
  static double PROB_ERR = 0.2;

  static std::random_device rd;
  static std::mt19937 seed{ rd() };
  static std::uniform_real_distribution<double> realDie{ 0.0, 1.0 };

  return realDie(seed) < PROB_ERR;
}

Answer genRandAns(TQuadPoly const& poly, TStudent const& student) {
  static std::random_device rd;
  static std::mt19937 seed{ rd() };

  static std::uniform_int_distribution<int> intDie{ 0, 3 };
  static std::uniform_real_distribution<double> realDie{ -100.0, 100.0 };

  std::array<double, 2> roots({ realDie(seed), realDie(seed) });
  return Answer(static_cast<ERootsFlag>(intDie(seed)), roots, poly, student.getName());
}

Answer genBadAns(TQuadPoly const& poly, TStudent const& student) {
  std::array<double, 2> roots({ 0.0, 0.0 });
  return Answer(ERootsFlag::RF_ONE_ROOT, roots, poly, student.getName());
}

Answer genGoodAns(TQuadPoly const& poly, TStudent const& student) {
  std::array<double, 2> roots({ 0.0, 0.0 });
  ERootsFlag flag = poly.solve(roots);
  return Answer(flag, roots, poly, student.getName());
}

TStudent::TStudent(std::string name)
  : name(name) 
{}

std::string TStudent::getName() const {
  return this->name;
}

void TStudent::sendAnswer(TProfessor& prof, TQuadPoly const& poly) const {
  prof.getAnswer(this->giveAnswer(poly));
}

Answer TBadStudent::giveAnswer(TQuadPoly const& poly) const {
  return genBadAns(poly, *this);
}

Answer TNormStudent::giveAnswer(TQuadPoly const& poly) const {
  if (isFail())
    return genRandAns(poly, *this);
  else {
    return genGoodAns(poly, *this);
  }
}

Answer TGoodStudent::giveAnswer(TQuadPoly const& poly) const {
  return genGoodAns(poly, *this);
}