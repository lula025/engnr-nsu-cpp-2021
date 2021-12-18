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





int main(int ac, char** av) {
    string filename, mode;
    ifstream file;


    //    po::options_description desc("Варианты запуска программы");
    string help = "Варианты запуска программы:\n"
        "\t-h - вывести help\n"
        "\t<filename> -m <mode> - запуск по имени файла и режиму (adler32, sum64)\n"
        "\t-m <mode> <filename>\n";
    if (ac == 1)
    {
        cerr  << "Ошибка: нет аргументов" << help <<endl;
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
            cerr  << "Ошибка: неизвестная команда" << help << endl;
        }
        return 1;
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
                cerr << "Ошибка: неизвестный способ расчета" << help <<endl;
                return 1;
            }
        }
        else
            {
            if ((strcmp(av[3], "adler32") == 0) || (strcmp(av[3], "sum64") == 0))
            {
                mode = av[3];
                filename = av[1];
            }
            else
                {
                cerr  << "Ошибка: неизвестный способ расчета" << help <<endl;
                return 1;
            }
        }
    }
    else
        {
        cerr  << "Ошибка: неизвестные комманды" << help << endl;
        return 1;
    }

    file.open(filename, std::ios::binary);

    if (!(file.is_open()))
    {
        cerr << "Файл не найден" << help <<endl;
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