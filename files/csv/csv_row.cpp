#include <sstream>
#include "csv_row.h"

size_t CSVRow::size() const {
  return cells.size();
}

std::string const& CSVRow::operator[](size_t index) const {
  return cells[index];
}

std::istream& operator>>(std::istream& stream, CSVRow& row) {
  row.cells.clear();

  std::string line;
  std::getline(stream, line);

  std::istringstream lineStream(line);
  std::string cell;

  while (std::getline(lineStream, cell, ',')) {
    row.cells.push_back(cell);
  }

  if (cell.empty()) {
    row.cells.push_back("");
  }

  return stream;
}
