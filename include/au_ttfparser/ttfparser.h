#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <vector>

class ttfparser {
public:
  // Constructor & destructor
  ttfparser(std::string path);
  ~ttfparser();

  // File opperation
  std::vector<unsigned char> read(uint nbBytes);
  void jump(uint jumpLenght);

  // File data fetcher
  void checkVersion();
  uint16_t numTable();

  // Bytes to int
  uint32_t bytesToInt32(const std::vector<unsigned char> &bytes);

private:
  std::ifstream fontFile;
};
