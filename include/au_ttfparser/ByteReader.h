#pragma once

#include <array>
#include <cstdint>
#include <stdint.h>
#include <vector>

class ByteReader {
public:
  ByteReader() = default;
  ByteReader(const uint8_t *buffer, size_t lenght)
      : buffer(buffer), lenght(lenght) {};

  // Read and move the pos
  uint16_t readU16();
  uint32_t readU32();
  std::array<uint8_t, 4> readTag();

  void move(size_t offset);
  size_t getPos();

  template <typename T> void printHex(T value);

private:
  const uint8_t *buffer;
  size_t lenght;
  size_t pos = 0;

  void outOfBoundException();
};
