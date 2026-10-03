#include "au_ttfparser/TTFFile.h"
#include <string>

int main(int argc, char *argv[]) {
  TTFFile file = TTFFile();
  file.load("/home/aurel/Downloads/anonymouspro/AnonymousPro-Regular.ttf");
  file.fetchTable();

  return 0;
}
