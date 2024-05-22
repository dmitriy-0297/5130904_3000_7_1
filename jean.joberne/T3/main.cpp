#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <iomanip>
#include "shapes.h"
#include "shape_operations.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return 1;
  }

  std::ifstream inputF(argv[1]);
  if (!inputF) {
    return 1;
  }

  std::vector<Shape> shapes;
  while (inputF) {
    Shape shape;
    inputF >> shape;
    if (inputF) {
      shapes.push_back(shape);
    }
    if (inputF.fail() && !inputF.eof()) {
      inputF.clear();
      inputF.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::string command;
  while (std::cin >> command) {
    try {
      if (command == "AREA") {
        area(shapes);
      } else if (command == "PERMS") {
        perms(shapes);
      } else if (command == "COUNT") {
        count(shapes);
      } else if (command == "MAX") {
        max(shapes);
      } else if (command == "MIN") {
        min(shapes);
      } else {
        throw std::invalid_argument("Invalid command");
      }
    } catch (...) {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
  }

  return 0;
}

