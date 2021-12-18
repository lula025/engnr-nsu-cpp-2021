//
// Created by bulga on 18.12.2021.
//

#pragma once
#include <iostream>
#include <fstream>
using namespace std;
const int mod_adler= 65521;
class Hash_fun{
public:
    static uint32_t adler32(ifstream& file);
    static uint64_t sum64(ifstream& file);
private:
    static uint64_t read_int(istream &file);
};


