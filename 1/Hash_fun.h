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
    static int adler32(ifstream& file);
    static int sum64(ifstream& file);
private:
    static int read_int(std::istream &file);
};


