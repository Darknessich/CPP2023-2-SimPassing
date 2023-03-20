#pragma once
#include <array>
#include <string>
#include "Professor.h"

class Student {
public:
  Student(std::string _name);
  std::string getName() const;
  void sendAnswer(Professor& prof, std::array<double, 3> const& _poly) const;
private:
  virtual Answer giveAnswer(std::array<double, 3> const& _poly) const = 0;
  std::string name;
};

class BadStudent : public Student {
public:
  BadStudent(std::string _name) : Student(_name) {};
private:
  Answer giveAnswer(std::array<double, 3> const& _poly) const;
};

class MidStudent : public Student {
public:
  MidStudent(std::string _name) : Student(_name) {};
private:
  Answer genRandAns(std::array<double, 3> const& _poly) const;
  Answer giveAnswer(std::array<double, 3> const& _poly) const;
};

class GoodStudent : public Student {
public:
  GoodStudent(std::string _name) : Student(_name) {};
private:
  Answer giveAnswer(std::array<double, 3> const& _poly) const;
};