#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t crcu8(uint8_t data, uint16_t crc) {
    uint8_t i = 0;
    uint8_t x16 = 0;
    uint8_t carry = 0;

    for (i = 0; i < 8; i++) {
        x16 = (uint8_t)((data & 1) ^ ((uint8_t)crc & 1));
        data >>= 1;

        if (x16 == 1) {
            crc ^= 0x4002;
            carry = 1;
        } else
            carry = 0;
        crc >>= 1;
        if (carry)
            crc |= 0x8000;
        else
            crc &= 0x7fff;
    }
    return crc;
}

uint16_t crcu16(uint16_t newval, uint16_t crc) {
    crc = crcu8((uint8_t)(newval), crc);
    crc = crcu8((uint8_t)((newval) >> 8), crc);
    return crc;
}

uint16_t crc16(int16_t newval, uint16_t crc) {
    return crcu16((uint16_t)newval, crc);
}

uint16_t crcu32(uint32_t newval, uint16_t crc) {
    crc = crc16((int16_t)newval, crc);
    crc = crc16((int16_t)(newval >> 16), crc);
    return crc;
}

int main() {
    printf("%" PRIu16 "\n", crcu32(0xFAFFBADD, 0));
}