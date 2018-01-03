#include <iostream>
#include <fstream>
#include <iomanip>
#include "csv_row.h"

int main() {
  std::ifstream file("grades.csv");

  CSVRow row;
  while (file >> row) {
    std::cout << std::left << std::setw(20) << row[0]
              << std::left << std::setw(20) << row[1]
              << std::left << std::setw(20) << row[2]
              << row[3]
              << '\n';
  }

  return 0;
}
