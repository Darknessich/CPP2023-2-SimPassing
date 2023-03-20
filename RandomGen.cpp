#include "RandomGen.h"
#include <random>

int getRandomNum(int min, int max) {
  static std::random_device rd;
  static std::mt19937 seed{ rd() };

  std::uniform_int_distribution<int> die{ min, max };
  return die(seed);
}

double getRandomNum(double min, double max) {
  static std::random_device rd;
  static std::mt19937 seed{ rd() };

  std::uniform_real_distribution<double> die{ min, max };
  return die(seed);
}