/**
* \file Header file describing students.
* 
* This file contains the declaration of 3 classes of students (good, normal
* and bad) as well as an abstract base class.
*/
#pragma once
#include "quadratic.h"
#include "professor.h"
#include <array>
#include <string>

class TStudent {
private:
  std::string name;

private:
  /**
  * The abstract method in which the student's answer is formed
  * 
  * \param [in] poly a given quadratic polynomial 
  * \return student response
  */
  virtual TAnswer giveAnswer(TQuadPoly const& poly) const = 0;

public:
  TStudent(std::string name);

  /// to get the student's name
  std::string getName() const;

  /**
  * sends the student's reply by email to the teacher
  * 
  * \param [in] prof Professor to whom a reply will be sent
  * \param [in] poly a given quadratic polynomial
  */
  void sendAnswer(TProfessor& prof, TQuadPoly const& poly) const;
};

class TBadStudent : public TStudent {
private:
  /// the student's answer is always one root: {0}
  TAnswer giveAnswer(TQuadPoly const& _poly) const;

public:
  TBadStudent(std::string name) : TStudent(name) {};
};

class TNormStudent : public TStudent {
private:
  /// the student's answer is sometimes not correct
  TAnswer giveAnswer(TQuadPoly const& _poly) const;

public:
  TNormStudent(std::string name) : TStudent(name) {};
};

class TGoodStudent : public TStudent {
private:
  /// the student's answer is always correct
  TAnswer giveAnswer(TQuadPoly const& _poly) const;

public:
  TGoodStudent(std::string name) : TStudent(name) {};
};