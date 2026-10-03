#include "au_ttfparser/TTFFile.h"
#include "au_ttfparser/ByteReader.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

void TTFFile::load(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  if (!file)
    throw std::runtime_error("cannot open file: " + path);

  std::streamsize size = file.tellg();
  if (size <= 0)
    throw std::runtime_error("empty or unreadable file");

  file.seekg(0, std::ios::beg);

  buffer.resize(static_cast<size_t>(size));
  if (!file.read(reinterpret_cast<char *>(buffer.data()), size))
    throw std::runtime_error("read failed");

  reader = ByteReader(buffer.data(), size);
}

void TTFFile::fetchTable() {
  version = reader.readU32();
  numTable = reader.readU16();
  reader.printHex(version);
  std::cout << numTable << std::endl;
}
