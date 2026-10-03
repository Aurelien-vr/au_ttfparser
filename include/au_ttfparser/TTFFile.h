#pragma once

#include "au_ttfparser/ByteReader.h"
#include "au_ttfparser/TableRecord.h"
#include <cstdint>
#include <string>

class TTFFile {
public:
  // Openning the file
  void load(const std::string &path);

  // TTF data methode
  void fetchTable();

private:
  // BytesReader
  ByteReader reader;

  // File management
  int file;
  size_t size;
  std::vector<uint8_t> buffer;

  // TTF file data
  uint32_t version;
  uint16_t numTable;

  // Table
  std::vector<TableRecord> tablesRecords;
};
