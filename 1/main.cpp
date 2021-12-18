// hesh_file.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iterator>
#include <exception>
#include <string>
#include <cstring>
#include "Hash_fun.h"

using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::ifstream;
using std::runtime_error;





int main(int ac, char** av) {
    string filename, mode;
    ifstream file;
    bool is_help=false;


    //    po::options_description desc("Варианты запуска программы");
    string consl = "Варианты запуска программы:\n"
        "\t-h - вывести help\n"
        "\t<filename> -m <mode> - запуск по имени файла и режиму (adler32, sum64)\n"
        "\t-m <mode> <filename>\n";
    for (int i = 0; i < ac; i++) {
        if (strcmp(av[i], "-h") == 0) {
            is_help = true;
        }
        else if (strcmp(av[i], "-m") == 0) {
            mode = string(av[i + 1]);
            i++;
        }
        else {
            filename= string(av[i]);
        }
    }
    try {

        if (is_help == 1 || mode == "" || filename == "") {
            cout << consl << "\n";
            return 0;
        }


        if (mode != "adler32" && mode != "sum64")
            throw runtime_error("Mode should be adler32 or sum64");

        file.open(filename, std::ios::binary);

        if (!file.is_open())
            throw runtime_error("File not found!");

        if (mode == "adler32") {
            int hash = Hashing::adler32(file);

            cout << "Hash: 0x" << std::hex << hash << "\n";
        }
        else {
            int hash = Hashing::sum64(file);

            cout << "Hash: 0x" << std::hex << hash << "\n";
        }

    }
    catch (exception& e) {
        cerr << "error: " << e.what() << "\n";
        cerr << "help: " << consl << "\n";
        return 1;
    }
    catch (...) {
        cerr << "Exception of unknown type!\n";
        return 1;
    }
    return 0;
}


