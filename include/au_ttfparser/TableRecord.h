#include <array>
#include <stdint.h>

struct TableRecord {
  std::array<uint8_t, 4> tag;
  uint32_t checksum;
  uint32_t offset;
  uint32_t lenght;
};
