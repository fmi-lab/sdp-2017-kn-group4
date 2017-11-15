#include <iostream>
#include <iomanip>
#include <queue>

using Position = std::tuple<int, int, int>;
using Labyrinth = std::vector<std::vector<std::string>>;

void print(Labyrinth const& labyrinth) {
  for (auto const& row : labyrinth) {
    for (auto const& cell : row) {
      std::cout << std::setw(4) << cell;
    }
    std::cout << '\n';
  }
}

bool inside_labyrinth(Position const& position, Labyrinth const& labyrinth) {
  int x, y, distance;
  std::tie(x, y, distance) = position;

  return x >= 0 && x < labyrinth.size() && y >= 0 && y < labyrinth.size();
}

bool empty(Position const& position, Labyrinth const& labyrinth) {
  int x, y, distance;
  std::tie(x, y, distance) = position;

  return labyrinth[y][x] == "o";
}

void traverse(Labyrinth& labyrinth, int x, int y) {
  std::queue<Position> q;
  q.push(Position(x, y, 0));

  while (!q.empty()) {
    Position current_position = q.front();
    q.pop();

    int x, y, distance;
    std::tie(x, y, distance) = current_position;

    Position next_positions[] = {
      Position(x - 1, y, distance + 1),
      Position(x + 1, y, distance + 1),
      Position(x, y - 1, distance + 1),
      Position(x, y + 1, distance + 1),
    };

    for (Position const& position : next_positions) {
      if (inside_labyrinth(position, labyrinth) &&
          empty(position, labyrinth)) {
        q.push(position);

        int x, y, distance;
        std::tie(x, y, distance) = position;
        labyrinth[y][x] = std::to_string(distance);
      }
    }
  }

  for (auto& row : labyrinth) {
    for (auto& cell : row) {
      if (cell == "o") {
        cell = "u";
      }
    }
  }
}

int main() {
  Labyrinth labyrinth = {
    { "o", "o", "o", "o", "o", "x", "x", "o" },
    { "o", "x", "o", "x", "x", "o", "x", "x" },
    { "o", "o", "x", "o", "x", "o", "o", "o" },
    { "o", "o", "o", "o", "x", "x", "x", "o" },
    { "o", "*", "o", "x", "o", "o", "o", "o" },
    { "o", "x", "x", "o", "o", "o", "o", "o" },
    { "o", "o", "o", "o", "x", "x", "x", "o" },
    { "x", "o", "x", "o", "o", "o", "o", "o" },
  };

  traverse(labyrinth, 1, 4);
  print(labyrinth);

  return 0;
}
