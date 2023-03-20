#include <list>
#include <array>
#include <iostream>
#include <fstream>
#include "Professor.h"
#include "Student.h"
#include "RandomGen.h"

enum class StType 
{
  GOOD = 1,
  MID  = 2,
  BAD  = 3
};

Student* newStudent(std::string name) {
  switch (static_cast<StType>(getRandomNum(1, 3))) {
  case StType::GOOD:
    return new GoodStudent(name);
  case StType::MID:
    return new MidStudent(name);
  case StType::BAD:
    return new BadStudent(name);
  default:
    return nullptr;
  };
}

void FillStudentList(std::istream& is, std::list<Student*>& list) {
  std::string name;
  while (getline(is, name))
    list.push_back(newStudent(name));
}

void FillPolyList(std::istream& is, std::list<std::array<double, 3>>& list) {
  std::array<double, 3> poly;
  while (!is.eof() && !is.fail()) {
    is >> poly.at(0) >> poly.at(1) >> poly.at(2);
    list.push_back(poly);
  }
}

void FreeStudentList(std::list<Student*>& list) {
  for (auto student : list)
    delete student;
  list.resize(0);
}

void SendAllAnswers(
  Professor& prof, std::list<Student*> const& sList, 
  std::list<std::array<double, 3>> const& pList) 
{
  for (auto const& poly : pList)
    for (auto student : sList)
      student->sendAnswer(prof, poly);
}

int main() {
  std::ifstream studentsFile("students.txt");
  std::ifstream polyFile("poly.txt");
  std::ofstream GradeTable("gradetable.txt", std::ios::out | std::ios::ate);

  std::list<Student*> studentList;
  std::list<std::array<double, 3>> polyList;
  Professor professor;

  FillStudentList(studentsFile, studentList);
  FillPolyList(polyFile, polyList);
  
  SendAllAnswers(professor, studentList, polyList);
  professor.checkAllAnswers();
  professor.createGradeTable(GradeTable);

  FreeStudentList(studentList);
}