#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <iostream>
#include <limits>
#include <algorithm>
#include "shape.h"
#include "shape_commands.h"

const int ERROR_CODE = 1;
const std::string ERROR_OPEN_FILE = "<ERROR OPENING FILE>";
const std::string ERROR_FILENAME_NOT_PROVIDED = "<FILENAME NOT PROVIDED>";
const std::string ERROR_INVALID_COMMAND = "<INVALID COMMAND>";

void readShapesFromFile(const char* filename, std::vector<Polygon>& shapes) {
  std::ifstream inputFile(filename);
  if (!inputFile) {
    throw std::runtime_error(ERROR_OPEN_FILE);
  }

  while (!inputFile.eof()) {
    Polygon shape;
    inputFile >> shape;
    if (inputFile) {
      shapes.push_back(shape);
    } else {
      inputFile.clear();
      inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << ERROR_FILENAME_NOT_PROVIDED << std::endl;
    return ERROR_CODE;
  }

  std::vector<Polygon> shapes;
  try {
    readShapesFromFile(argv[1], shapes);
  } catch (const std::exception& e) {
    std::cerr << ERROR_OPEN_FILE << std::endl;
    return ERROR_CODE;
  }

  std::cin.clear();
  std::string command;
  while (std::cin >> command) {
    try {
      if (command == "PERMS") {
        perms(shapes);
      } else if (command == "AREA") {
        area(shapes);
      } else if (command == "MAX") {
        max(shapes);
      } else if (command == "MIN") {
        min(shapes);
      } else if (command == "COUNT") {
        count(shapes);
      } else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument(ERROR_INVALID_COMMAND);
      }
    } catch (const std::exception& e) {
      std::cout << ERROR_INVALID_COMMAND << std::endl;
    }
  }

  return 0;
}
