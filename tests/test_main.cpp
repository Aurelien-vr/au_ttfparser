#include "au_ttfparser/ttfparser.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  // Make sure a path was provided
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <file-path>\n";
    return 1;
  }

  std::string path = argv[1];

  ttfparser parser(path);
  parser.checkVersion();
  parser.numTable();

  return 0;
}
