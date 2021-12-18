// hash_file.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "Hash_fun.h"

using std::cerr;
using std::hex;
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::ifstream;
using std::runtime_error;





int main(int ac, char* av[]) {
    string filename, mode;
    ifstream file;


    //    po::options_description desc("Варианты запуска программы");
    string help = "Using:\n"
        "\t-h - help\n"
        "\t<filename> -m <mode> - setup by mode (adler32, sum64)\n"
        "\t-m <mode> <filename> - setup by mode\n";
    if (ac == 1|| ac==0)
    {
        cerr  << "Error: empty list of arguments" << help <<endl;
        return 1;
    }
    else if(ac==2){
        if(strcmp(av[1], "-h") == 0)
        {
            cout << help <<endl;
            return 0;
        }
        else
        {
            cerr  << "Error: wrong command" << help << endl;
            return 1;
        }
    }
    else if (ac == 4) {
        if (strcmp(av[1], "-m") == 0)
        {
            if (strcmp(av[2], "adler32") == 0 || strcmp(av[2], "sum64") == 0)
            {
                mode = av[2];
                filename = av[3];
            }
            else
                {
                cerr << "Error: undefined way to calculate" << help <<endl;
                return 1;
            }
        }
        else if (strcmp(av[2], "-m") == 0)
            {
            if ((strcmp(av[3], "adler32") == 0) || (strcmp(av[3], "sum64") == 0))
            {
                mode = av[3];
                filename = av[1];
            }
            else
                {
                cerr  << "Error: undefined way to calculate" << help <<endl;
                return 1;
            }
        }
    }
    else
        {
        cerr  << "Error: undefined commands" << help << endl;
        return 1;
    }

    file.open(filename, std::ios::in|std::ios::binary);

    if (!(file.is_open()))
    {
        cerr << "File not found" << help <<endl;
        return 1;
    }
    else if(file.peek() == EOF)
    {
        if(mode == "adler32")
        {
            cout << 1 << endl;
        }
        else
            {
            cout << 0 << endl;
        }
        return 0;
    }

    try {
        if (mode == "adler32")
        {
            cout << hex << Hash_fun::adler32(file) <<endl;
        }
        else
            {
            cout << hex << Hash_fun::sum64(file) << endl;
        }
    }
    catch (exception &e)
    {
        cerr << e.what() <<endl;
        return 1;
    }
    return 0;
}