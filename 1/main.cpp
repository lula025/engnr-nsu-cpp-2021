// hash_file.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cstring>
#include "Hash_fun.h"







int main(int ac, char* av[]) {
    std::string filename, mode;
    std::ifstream file;


    //    po::options_description desc("Варианты запуска программы");
    std::string help = "Using:\n"
        "\t-h - help\n"
        "\t<filename> -m <mode> - setup by mode (adler32, sum64)\n"
        "\t-m <mode> <filename> - setup by mode\n";
    if (ac == 1|| ac==0)
    {
        std::cerr  << "Error: empty list of arguments" << help <<std::endl;
        return 1;
    }
    else if(ac==2){
        if(strcmp(av[1], "-h") == 0)
        {
            std::cout << help <<std::endl;
            return 0;
        }
        else
        {
            std::cerr  << "Error: wrong command" << help <<std:: endl;
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
                std::cerr << "Error: undefined way to calculate" << help <<std::endl;
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
                std::cerr  << "Error: undefined way to calculate" << help <<std::endl;
                return 1;
            }
        }
    }
    else
        {
        std::cerr  << "Error: undefined commands" << help << std::endl;
        return 1;
    }

    file.open(filename, std::ios::in|std::ios::binary);

    if (!(file.is_open()))
    {
        std::cerr << "File not found" << help <<std::endl;
        return 1;
    }
//   else if(file.peek() == EOF)
//   {
//        if(mode == "adler32")
//        {
//            std::cout << 1 << std::endl;
//        }
//        else
//            {
//            std::cout << 0 <<std::endl;
//        }
//        return 0;
//    }

    try {
        if (mode == "adler32")
        {
            std::cout << hex << Hash_fun::adler32(file) <<std::endl;
        }
        else
            {
            std::cout << hex << Hash_fun::sum64(file) << std::endl;
        }
    }
    catch (exception &e)
    {
        std::cerr << e.what() <<std::endl;
        return 1;
    }
    return 0;
}