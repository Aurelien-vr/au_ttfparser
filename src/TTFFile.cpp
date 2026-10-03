#include "au_ttfparser/TTFFile.h"
#include "au_ttfparser/ByteReader.h"
#include <cstdint>
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

  // Read the first two entry of the file
  version = reader.readU32();
  numTable = reader.readU16();

  // Move 6 bytes
  // Skip: searchRange, entrySelector, rangeShift
  reader.move(6);

  for (int i = 0; i < numTable; i++) {
    TableRecord tableRecord = TableRecord{reader.readTag(), reader.readU32(),
                                          reader.readU32(), reader.readU32()};
    tablesRecords.push_back(tableRecord);
  }

  // DEBUG print
  reader.printHex(version);
  std::cout << numTable << std::endl;

  for (TableRecord tableRecord : tablesRecords) {

    std::cout << "====TABLE====" << std::endl << "TAG: ";
    for (uint8_t chara : tableRecord.tag) {
      std::cout << (char)chara;
    }
    std::cout << std::endl;
    std::cout << "Check sum: " << tableRecord.checksum << std::endl;
    std::cout << "Offset: " << tableRecord.offset << std::endl;
    std::cout << "Lenght: " << tableRecord.lenght << std::endl << std::endl;
  }
}
