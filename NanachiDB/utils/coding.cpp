#include "coding.h"

uint32_t DecodeFixed32(const char* s) {
    const uint8_t* const buffer = reinterpret_cast<const uint8_t*>(s);

    return (static_cast<uint32_t>(buffer[0])) |
           (static_cast<uint32_t>(buffer[1] << 8)) |
           (static_cast<uint32_t>(buffer[2] << 16)) |
           (static_cast<uint32_t>(buffer[3] << 24));
}