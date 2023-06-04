#include "hash.h"

#include <climits>
#include <cmath>

namespace solution {

inline static uint32_t funF(uint32_t x, uint32_t y, uint32_t z) {
  return (x & y) | (~x & z);
}

inline static uint32_t funG(uint32_t x, uint32_t y, uint32_t z) {
  return (x & z) | (~z & y);
}

inline static uint32_t funH(uint32_t x, uint32_t y, uint32_t z) {
  return x ^ y ^ z;
}

inline static uint32_t funI(uint32_t x, uint32_t y, uint32_t z) {
  return y ^ (~z | x);
}

inline static uint32_t left_rotate(uint32_t value, uint32_t shift) {
  return (value << shift) |
         ((value & (~static_cast<uint32_t>(0) << (32 - shift))) >>
          (32 - shift));
}

std::string hash_sum(std::string text) {
  static const uint32_t s[64] = {
      7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
      5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
  uint32_t K[64];
  for (uint32_t i = 0; i < 64; ++i) {
    K[i] = static_cast<uint32_t>(
        std::floor(std::abs(std::sin(i + 1)) * (1ULL << 32)));
  }

  const uint64_t len = text.size();
  uint32_t additional_bits = 448 - (len * CHAR_BIT) % 512;
  if (additional_bits <= 0) {
    additional_bits += 512;
  }
  text += static_cast<char>(1 << (CHAR_BIT - 1));
  additional_bits -= CHAR_BIT;
  text.append(additional_bits / CHAR_BIT, 0);
  text.append(reinterpret_cast<const char *>(&len), sizeof(len));

  uint32_t wordA0 = 0x67452301;
  uint32_t wordB0 = 0xEFCDAB89;
  uint32_t wordC0 = 0x98BADCFE;
  uint32_t wordD0 = 0x10325476;

  const size_t step = 512 / CHAR_BIT;
  for (size_t i = 0; i < text.size(); i += step) {
    const uint32_t *M = reinterpret_cast<const uint32_t *>(text.data() + i);
    uint32_t A = wordA0;
    uint32_t B = wordB0;
    uint32_t C = wordC0;
    uint32_t D = wordD0;

    for (size_t j = 0; j < 64; ++j) {
      uint32_t F = 0;
      uint32_t g = 0;
      if (j < 16) {
        F = funF(B, C, D);
        g = j;
      } else if (j < 32) {
        F = funG(B, C, D);
        g = (5 * j + 1) % 16;
      } else if (j < 48) {
        F = funH(B, C, D);
        g = (3 * j + 5) % 16;
      } else {
        F = funI(B, C, D);
        g = (7 * j) % 16;
      }
      F = F + A + K[j] + M[g];
      A = D;
      D = C;
      C = B;
      B = B + left_rotate(F, s[j]);
    }
    wordA0 = wordA0 + A;
    wordB0 = wordB0 + B;
    wordC0 = wordC0 + C;
    wordD0 = wordD0 + D;
  }

  std::string result;
  result.append(reinterpret_cast<const char *>(&wordA0), sizeof(wordA0));
  result.append(reinterpret_cast<const char *>(&wordB0), sizeof(wordB0));
  result.append(reinterpret_cast<const char *>(&wordC0), sizeof(wordC0));
  result.append(reinterpret_cast<const char *>(&wordD0), sizeof(wordD0));

  return result;
}

}  // namespace solution
