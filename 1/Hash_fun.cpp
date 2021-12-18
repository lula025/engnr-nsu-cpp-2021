//
// Created by bulga on 18.12.2021.
//

#include "Hash_fun.h"
#include <iostream>
uint32_t Hash_fun::adler32(std::istream& file) {
    unsigned char temp;
    uint32_t a = 1, b = 0;

    while (file.read((char *)(&temp), sizeof(unsigned char)))
    {
        a = (a + temp) % mod_adler;
        b = (b + a) % mod_adler;
    }

    return (b << 16) | a;
}


uint64_t Hash_fun::sum64(std::istream &file) {
    uint64_t result = 0;

    while (!file.eof()) {
        unsigned char count;
        uint64_t temp = 0;

        for (int i = 0; i < 8; i++) {
            file.read((char*)(&count), sizeof(unsigned char));
            if (file.eof())
                break;
            temp = (temp << 8) | count;
        }

        result += temp;
    }

    return result;
}
