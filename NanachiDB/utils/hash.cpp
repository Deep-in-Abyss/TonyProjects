#include "hash.h"


uint32_t Hash(const char* data, size_t n, uint32_t seed) {
    const uint32_t m = 0xc6a4a793;
    const uint32_t r = 24;
    const char* limit = data + n;
    uint32_t res = seed ^ (n * m);

    while(data + 4 <= limit) {
        uint32_t w = DecodeFixed32(data);
        data += 4;
        res += w;
        res *= m;
        res ^= (res >> 16);
    }

    switch (limit - data)
    {
        case 3:
            res += static_cast<uint8_t>(data[2]) << 16;
        case 2:
            res += static_cast<uint8_t>(data[1]) << 8;
        case 1:
            res += static_cast<uint8_t>(data[0]);
            res *= m;
            res ^= (res >> r);
            break;
    }

    return res;
}