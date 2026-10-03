#include "au_ttfparser/ByteReader.h"
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <type_traits>

size_t ByteReader::getPos() {
  outOfBoundException();
  return pos;
}

// Shift bits to create larger bytes than the buffer
uint16_t ByteReader::readU16() {
  if ((pos + 2) >= lenght)
    throw std::runtime_error("Out of buffer bound 16");
  uint16_t result = (buffer[pos] << 8) | buffer[pos + 1];
  pos += 2;
  return result;
}

// Shift bits to create larger bytes than the buffer
uint32_t ByteReader::readU32() {
  if ((pos + 4) >= lenght)
    throw std::runtime_error("Out of buffer bound 32");
  uint32_t result =
      (uint32_t(buffer[pos]) << 24) | (uint32_t(buffer[pos + 1]) << 16) |
      (uint32_t(buffer[pos + 2]) << 8) | uint32_t(buffer[pos + 3]);
  pos += 4;
  return result;
}

std::array<uint8_t, 4> ByteReader::readTag() {
  if ((pos + 4) >= lenght)
    throw std::runtime_error("Out of buffer bound");

  std::array<uint8_t, 4> result;
  for (int i = 0; i < 4; i++) {
    result[i] = buffer[pos + i];
  }
  pos += 4;
  return result;
}

void ByteReader::move(size_t offset) {
  if ((pos + offset) >= lenght)
    throw std::runtime_error("Out of buffer bound");

  pos += offset;
}

void ByteReader::outOfBoundException() {
  if (pos >= lenght)
    throw std::runtime_error("Out of buffer bound");
}

template <typename T> void ByteReader::printHex(T value) {
  static_assert(std::is_unsigned<T>::value,
                "T must be an unsigned integer type");
  std::cout << "0x" << std::hex << std::uppercase << std::setw(sizeof(T) * 2)
            << std::setfill('0') << static_cast<uint64_t>(value) << std::dec
            << std::endl;
}

template void ByteReader::printHex<uint8_t>(uint8_t);
template void ByteReader::printHex<uint16_t>(uint16_t);
template void ByteReader::printHex<uint32_t>(uint32_t);
template void ByteReader::printHex<uint64_t>(uint64_t);
