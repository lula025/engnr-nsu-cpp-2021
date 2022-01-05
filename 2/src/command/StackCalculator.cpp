#include "StackCalculator.h"

void StackCalc::command(std::unique_ptr<Command> cmd)
{
    cmd->command(context_execution);
}

Command *StackCalc::read_command(std::string &command_line)
{
    std::string help = "Usage: ./Calculator <filepath> or ./Calculator"
                       "Commands: #, POP, PUSH <number>, PUSH <varname>, PEEK <varname>, ABS, PLUS, MINUS, MULT, DIV, PRINT, READ.";
    std::string command;
    std::stringstream x;
    x << command_line;
    x >> command;
    Command *operation;
    //уроды могли бы свитч для стррок в схх сделать
    if (command.empty()) {
        return nullptr;
    } else if (command == "POP") {
        operation = new Pop(command);
    } else if (command == "PUSH") {
        x >> command;
        operation = new Push(command);
    } else if (command == "PEEK") {
        x >> command;
        operation = new Peek(command);
    } else if (command == "ABS") {
        operation = new Abs(command);
    } else if (command == "PLUS") {
        operation = new Plus(command);
    } else if (command == "MINUS") {
        operation = new Minus(command);
    } else if (command == "MUL") {
        operation = new Multiply(command);
    } else if (command == "DIV") {
        operation = new Division(command);
    } else if (command == "PRINT") {
        operation = new Print(command);
    } else if (command == "READ") {
        operation = new Read(command);
    } else {
        if (command != "#") {
            throw UnknownCommand("Unknown command: " + command);
        } else {
            operation = new Comment(command);
        }
    }
    return operation;
}


StackCalc OneCommandRead()
{
    StackCalc calculator;
    std::string command_line = "s";
    while (!std::cin.eof())
    {
        getline(std::cin, command_line);
        if (command_line.empty()) continue;
        std::unique_ptr<Command> cmd(calculator.read_command(command_line));
        if (cmd == nullptr)
        {
            continue;
        }
        calculator.command(std::move(cmd));
    }
    return calculator;
}

StackCalc ReadFromStream(std::istream &file)
{
    StackCalc calculator;
    std::string command_line;
    while (!file.eof())
    {
        std::getline(file, command_line);
        std::unique_ptr<Command> cmd(calculator.read_command(command_line));
        if (cmd == nullptr) continue;
        calculator.command(std::move(cmd));
    }
    return calculator;
}