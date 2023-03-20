#include "Student.h"
#include "Quadratic.h"
#include "RandomGen.h"

// Probability of an mid student's error
static const double PROB_ERR = 0.2;

Student::Student(std::string name)
  : name(name) 
{}

std::string Student::getName() const {
  return this->name;
}

void Student::sendAnswer(Professor& prof, std::array<double, 3> const& _poly) const {
  prof.getAnswer(this->giveAnswer(_poly));
}

Answer BadStudent::giveAnswer(std::array<double, 3> const& _poly) const {
  std::array<double, 2> roots({ 0.0, 0.0 });
  return { rootsFlag::ONE_ROOT, roots, _poly, this->getName() };
}

Answer MidStudent::genRandAns(std::array<double, 3> const& _poly) const {
  std::array<double, 2> roots({ getRandomNum(-100.0, 100.0), getRandomNum(-100.0, 100.0) });
  return { static_cast<rootsFlag>(getRandomNum(0, 3)), roots, _poly, this->getName() };
}

Answer MidStudent::giveAnswer(std::array<double, 3> const& _poly) const {
  if (getRandomNum(0.0, 1.0) < PROB_ERR)
    return this->genRandAns(_poly);
  else {
    std::array<double, 2> roots({ 0.0, 0.0 });
    rootsFlag flag = Solve(_poly, roots);
    return { flag, roots, _poly, this->getName() };
  }
}

Answer GoodStudent::giveAnswer(std::array<double, 3> const& _poly) const {
  std::array<double, 2> roots({0.0, 0.0});
  rootsFlag flag = Solve(_poly, roots);
  return { flag, roots, _poly, this->getName() };
}