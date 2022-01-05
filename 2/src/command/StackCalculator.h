//
// Created by bulga on 03.01.2022.
//
#pragma once
#include <stack>
#include <map>
#include <string>
#include <iostream>
#include "Commands.h"
class StackCalc
        {
    ContextExecution context_execution;
        public:
            void command(std::unique_ptr<Command> cmd);
            Command *read_command(std::string &command_line);
            std::map<std::string, SafeInt<int64_t, CustomException>> FindResult()
            {
                return context_execution.variables;
            }
};

StackCalc ReadFromStream(std::istream &str);

StackCalc OneCommandRead();