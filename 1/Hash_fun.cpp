//
// Created by bulga on 18.12.2021.
//

#include "Hash_fun.h"
#include <Winsock2.h>
int Hashing::read_int(std::istream &file) {
    char temp;
    int num = 0, count = 0;

    while (!file.eof() && count < sizeof(uint64_t)){
        file.read((char*)&temp, sizeof(char));
        std::streamsize bytes = file.gcount();
        if (!bytes) break;

        num <<= 8; num |= temp;
        count++;
    }
    return num;
}
int Hashing::adler32(std::ifstream& file) {
    char temp;
    int a = 1, b = 0;

    while (!file.eof()) {
        file.read((char *)&temp, sizeof(char));
        std::streamsize count = file.gcount();

        a = (a + temp) % mod_adler;
        b = (b + a) % mod_adler;
    }

    return (b << 16) | a;
}


int Hashing::sum64(std::ifstream& file) {
    int sum = 0;

    while (!file.eof())
        sum += read_int(file);

    return sum;
}

