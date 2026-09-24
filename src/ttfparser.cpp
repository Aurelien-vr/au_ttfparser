#include "au_ttfparser/ttfparser.h"
#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

ttfparser::ttfparser(std::string path) : fontFile(path, std::ios::binary) {
  if (!fontFile.is_open()) {
    std::cerr << "Could not open file: " << path << '\n';
    throw std::runtime_error("Could not open file: " + path);
  }
}

std::vector<unsigned char> ttfparser::read(uint nbBytes) {
  std::vector<unsigned char> bytes(nbBytes);

  fontFile.read(reinterpret_cast<char *>(bytes.data()),
                static_cast<std::streamsize>(bytes.size()));

  if (!fontFile) {
    throw std::runtime_error("Could not read requested bytes");
  }

  return bytes;
}

void ttfparser::jump(uint jumpLenght) {
  fontFile.seekg(jumpLenght, std::ios::beg);
}

ttfparser::~ttfparser() {}

void ttfparser::checkVersion() {
  std::vector<unsigned char> version = read(4);

  std::vector<unsigned char> universalVersion = {0x00, 0x01, 0x00, 0x00};

  if (version != universalVersion) {
    std::cerr << "Error: invalid sfntVersion" << std::endl;
    std::exit(1);
  }

  std::cout << "Version: ";
  for (unsigned char byte : version) {
    std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(byte) << ' ';
  }
}

uint16_t ttfparser::numTable() {
  jump(4);
  std::vector<unsigned char> numTab = read(2);
  uint32_t numTabInt = bytesToInt32(numTab);
  std::cout << "number of table: " << numTabInt << std::endl;
  return numTabInt;
}

uint32_t ttfparser::bytesToInt32(const std::vector<unsigned char> &bytes) {
  uint32_t result = 0;

  for (size_t i = 0; i < bytes.size(); ++i) {
    result = (result << 8) | bytes[i];
  }

  return result;
}
