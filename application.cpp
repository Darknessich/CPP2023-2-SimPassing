#include "application.h"
#include "quadratic.h"
#include "professor.h"
#include "student.h"
#include <list>
#include <random>
#include <fstream>
#include <iostream>

enum class EMenuItem {
  MI_EXIT = 0,
  MI_ST_LIST,
  MI_POLY_LIST,
  MI_PUSH_ANS,
  MI_PRINT_TABLE
};

void PrintMenu() {
  std::cout << "1. Make a list of students" << std::endl;
  std::cout << "2. Make a list of quadratic polynomials" << std::endl;
  std::cout << "3. Accept and check all student responses" << std::endl;
  std::cout << "4. Print of a student grade table" << std::endl;
  std::cout << "0. Exit" << std::endl;
}

TStudent* newStudent(std::string name) {
  static std::random_device rd;
  static std::mt19937 seed{ rd() };
  static std::uniform_int_distribution<int> intDie{ 1, 3 };

  enum class EStudentType {
    ST_GOOD = 1,
    ST_NORM,
    ST_BAD
  };

  switch (static_cast<EStudentType>(intDie(seed))) {
  case EStudentType::ST_GOOD:
    return new TGoodStudent(name);
  case EStudentType::ST_NORM:
    return new TNormStudent(name);
  case EStudentType::ST_BAD:
    return new TBadStudent(name);
  default:
    return nullptr;
  };
}

void MakeStList(std::list<TStudent*>& stList) {
  std::string fileName;
  std::ifstream studentsFile;

  std::cout << "Enter the path to the list file:" << std::endl;
  std::getline(std::cin, fileName);
  studentsFile.open(fileName);

  if (studentsFile.is_open()) {
    std::string name;
    while (std::getline(studentsFile, name))
      stList.push_back(newStudent(name));

    std::cout << "Student list successfully created\n" << std::endl;
  }
  else {
    std::cout << "Unable to find the file\n" << std::endl;
  }
}

void MakePolyList(std::list<TQuadPoly>& polyList) {
  std::string fileName;
  std::ifstream polyFile;

  std::cout << "Enter the path to the list file:" << std::endl;
  std::getline(std::cin, fileName);
  polyFile.open(fileName);

  if (polyFile.is_open()) {
    double a, b, c;
    while (!polyFile.eof() && !polyFile.fail()) {
      polyFile >> a >> b >> c;
      polyList.push_back(TQuadPoly(a, b, c));
    }

    std::cout << "List of quadratic polynomials successfully created\n" << std::endl;
  }
  else {
    std::cout << "Unable to find the file\n" << std::endl;
  }
}

void SendAllToProfessor(
  TProfessor& prof,
  std::list<TStudent*>& stList,
  std::list<TQuadPoly>& polyList)
{
  std::cout << "answers accepted..." << std::endl;
  for (auto const& poly : polyList)
    for (auto const& student : stList)
      student->sendAnswer(prof, poly);

  std::cout << "the answers are checked..." << std::endl;
  prof.checkAllAnswers();
  std::cout << "answers receivedand checked!\n" << std::endl;
}

void PrintStudentsGradeTable(TProfessor const& prof) {
  std::string fileName;
  std::ofstream GradeTable;

  std::cout << "Enter the path to the list file:" << std::endl;
  std::getline(std::cin, fileName);
  GradeTable.open(fileName, std::ios::out | std::ios::ate);

  if (GradeTable.is_open()) {
    prof.printGradeTable(GradeTable);
    std::cout << "The student achievement table is written down!\n" << std::endl;
  }
  else {
    std::cout << "Failed to open file\n" << std::endl;
  }
}

void FreeStudentList(std::list<TStudent*>& list) {
  for (auto student : list)
    delete student;
  list.resize(0);
}

void TakeAction(
  EMenuItem selectedItem,
  std::list<TStudent*>& stList,
  std::list<TQuadPoly>& polyList,
  TProfessor& prof)
{
  switch (selectedItem)
  {
  case EMenuItem::MI_EXIT:
    std::cout << "Exit..." << std::endl;
    FreeStudentList(stList);
    break;
  case EMenuItem::MI_ST_LIST:
    MakeStList(stList);
    break;
  case EMenuItem::MI_POLY_LIST:
    MakePolyList(polyList);
    break;
  case EMenuItem::MI_PUSH_ANS:
    SendAllToProfessor(prof, stList, polyList);
    break;
  case EMenuItem::MI_PRINT_TABLE:
    PrintStudentsGradeTable(prof);
    break;
  default:
    std::cout << "This menu item does not exist!\n" << std::endl;
    break;
  }
}

int TApplication::exec() {
  TProfessor prof;
  std::list<TStudent*> stList;
  std::list<TQuadPoly> polyList;

  int selectedItem = -1;
  std::string cleaner;
  while (static_cast<EMenuItem>(selectedItem) != EMenuItem::MI_EXIT) {
    PrintMenu();
    std::cout << "select menu item: ";
    std::cin >> selectedItem;
    std::getline(std::cin, cleaner);
    std::cout << std::endl;
    TakeAction(static_cast<EMenuItem>(selectedItem), stList, polyList, prof);
  }

  return 0;
}
