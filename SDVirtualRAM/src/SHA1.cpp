// SHA1.cpp
#include "SHA1.h"
#include <string.h>
#include <avr/pgmspace.h>

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

void SHA1_Transform(uint32_t state[5], const uint8_t buffer[64]);

void SHA1_Init(SHA1_CTX* context) {
  context->state[0] = 0x67452301;
  context->state[1] = 0xEFCDAB89;
  context->state[2] = 0x98BADCFE;
  context->state[3] = 0x10325476;
  context->state[4] = 0xC3D2E1F0;
  context->count[0] = context->count[1] = 0;
}

void SHA1_Update(SHA1_CTX* context, const uint8_t* data, size_t len) {
  size_t i, j;
  j = (context->count[0] >> 3) & 63;
  if ((context->count[0] += len << 3) < (len << 3))
    context->count[1]++;
  context->count[1] += (uint32_t)(len / (1UL << 31));

  if ((j + len) > 63) {
    memcpy(&context->buffer[j], data, (i = 64 - j));
    SHA1_Transform(context->state, context->buffer);
    for (; i + 63 < len; i += 64) {
      SHA1_Transform(context->state, &data[i]);
    }
    j = 0;
  } else {
    i = 0;
  }
  memcpy(&context->buffer[j], &data[i], len - i);
}

void SHA1_Final(uint8_t digest[20], SHA1_CTX* context) {
  uint8_t finalcount[8];
  for (int i = 0; i < 8; i++) {
    finalcount[i] = (uint8_t)((context->count[(i >= 4 ? 0 : 1)] >>
                               ((3 - (i & 3)) * 8)) &
                              255); // Endian swap
  }

  SHA1_Update(context, (uint8_t *)"\200", 1);
  while ((context->count[0] & 504) != 448)
    SHA1_Update(context, (uint8_t *)"\0", 1);

  SHA1_Update(context, finalcount, 8); // Append length

  for (int i = 0; i < 20; i++) {
    digest[i] =
        (uint8_t)((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
  }

  memset(context, 0, sizeof(*context)); // Wipe context
}

void SHA1_Transform(uint32_t state[5], const uint8_t buffer[64]) {
  uint32_t a, b, c, d, e, t, i;
  uint32_t block[80];

  for (i = 0; i < 16; i++) {
    block[i] = ((uint32_t)buffer[4 * i + 0] << 24) |
               ((uint32_t)buffer[4 * i + 1] << 16) |
               ((uint32_t)buffer[4 * i + 2] << 8) |
               ((uint32_t)buffer[4 * i + 3]);
  }
  for (; i < 80; i++) {
    block[i] = rol(block[i - 3] ^ block[i - 8] ^ block[i - 14] ^ block[i - 16], 1);
  }

  a = state[0];
  b = state[1];
  c = state[2];
  d = state[3];
  e = state[4];

  for (i = 0; i < 80; i++) {
    if (i < 20)
      t = ((b & c) | ((~b) & d)) + 0x5A827999;
    else if (i < 40)
      t = (b ^ c ^ d) + 0x6ED9EBA1;
    else if (i < 60)
      t = ((b & c) | (b & d) | (c & d)) + 0x8F1BBCDC;
    else
      t = (b ^ c ^ d) + 0xCA62C1D6;

    t += rol(a, 5) + e + block[i];
    e = d;
    d = c;
    c = rol(b, 30);
    b = a;
    a = t;
  }

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;

  memset(block, 0, sizeof(block)); // Clear RAM
}
