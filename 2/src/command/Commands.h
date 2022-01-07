//
// Created by bulga on 03.01.2022.
//

#pragma once
#include <string>
#include <stack>
#include <map>
#include <sstream>
#include <cmath>
#include <iostream>
#include <utility>
#include "../../SafeInt/SafeInt.hpp"
#include <memory>

//abstract exception class
class StackException : public std::runtime_error
        {
    std::string message = "Error: ";
        public:
            explicit StackException(const std::string &ExMessage) : runtime_error(ExMessage),message(ExMessage) {};
            const char *excp() const noexcept  {
                return message.c_str();
            }
};

//exception classes
//wrong argument exceptions
class WrongArgument : public StackException
        {
        public:
            explicit WrongArgument(const std::string &ExMessage) : StackException(ExMessage) {}
            WrongArgument() : StackException("WrongArg") {}
};

class PushException : public WrongArgument
        {
        public:
            explicit PushException(const std::string &ExMessage) : WrongArgument(ExMessage) {}
            PushException() : WrongArgument("PUSH operation failed.") {}
};

class ReadException : public WrongArgument
        {
        public:
            explicit ReadException(const std::string &ExMessage) : WrongArgument(ExMessage) {}
            ReadException() : WrongArgument("READ operation failed.") {}
};

//empty stack exceptions
class EmptyStack : public StackException
        {
        public:
            explicit EmptyStack(const std::string &ExMessage) : StackException(ExMessage) {}
            EmptyStack() : StackException("Stack is Empty") {}
};

class PopException : public EmptyStack
        {
        public:
            explicit PopException(const std::string &ExMessage) : EmptyStack(ExMessage) {}
            PopException() : EmptyStack("POP operation failed.") {}
};

class PeekException : public EmptyStack
        {
        public:
            explicit PeekException(const std::string &ExMessage) : EmptyStack(ExMessage) {}
            PeekException() : EmptyStack("PEEK operation failed.") {}
};

class PrintException : public EmptyStack
        {
        public:
            explicit PrintException(const std::string &ExMessage) : EmptyStack(ExMessage) {}
            PrintException() : EmptyStack("PRINT operation failed.") {}
};

class AbsException : public EmptyStack
        {
        public:
            explicit AbsException(const std::string &ExMessage) : EmptyStack(ExMessage) {}
            AbsException() : EmptyStack("ABS operation failed.") {}
};

// Not enough element exception
class NEElement: public StackException
        {
        public:
            explicit NEElement(const std::string &ExMessage) : StackException(ExMessage) {}
            NEElement() : StackException("NotEnoughElement") {}
};

// unknown command exception
class UnknownCommand : public StackException
        {
        public:
            explicit UnknownCommand(const std::string &ExMessage) : StackException(ExMessage) {}
            UnknownCommand() : StackException("Unknown command was found") {}
};

// overflow exception
class OverflowException : public StackException
        {
        public:
            explicit OverflowException(const std::string &ExMessage) : StackException(ExMessage) {}
            OverflowException() : StackException("Overflow happened") {}
};

// division by xero exception
class DivisionByZero : public StackException
        {
        public:
            explicit DivisionByZero(const std::string &ExMessage) : StackException(ExMessage) {}
            DivisionByZero() : StackException("DivisionByZeroError") {}
};

class CustomException : public SafeIntException{
public:
    static void SafeIntOnOverflow();
    static void SafeIntOnDivZero();
};

// context executing
struct ContextExecution {
    std::stack<SafeInt<int64_t, CustomException>> stack;
    std::map<std::string, SafeInt<int64_t, CustomException>> variables;
};

// abstract command class
class Command
        {
        public:
            explicit Command(std::string &args) { params = args; }

            virtual void command(ContextExecution &context_execution) = 0;
            virtual ~Command() = default;
        protected:
            std::string params;
};

// stack commands classes
class Pop : public Command
        {
        public:
            explicit Pop(std::string &args);
            void command(ContextExecution &context_execution) override;

};

class Push : public Command
        {
        public:
            explicit Push(std::string &args);
            void command(ContextExecution &context_execution) override;
};

class Peek : public Command
        {
        public:
            explicit Peek(std::string &args);
            void command(ContextExecution &context_execution) override;
};

//Unary command
class Abs : public Command
        {
        public:
            explicit Abs(std::string &args);
            void command(ContextExecution &context_execution) override;
};

// Binary command
class Plus : public Command
        {
        public:
            explicit Plus(std::string &args);
            void command(ContextExecution &context_execution) override;
};

class Minus : public Command
        {
        public:
            explicit Minus(std::string &args);
            void command(ContextExecution &context_execution) override;
};

class Multiply : public Command
        {
        public:
            explicit Multiply(std::string &args);
            void command(ContextExecution &context_execution) override;
};

class Division : public Command
        {
        public:
            explicit Division(std::string &args);
            void command(ContextExecution &context_execution) override;
};

//  reading-printing commands
class Read : public Command
        {
        public:
            explicit Read(std::string &args);
            void command(ContextExecution &context_execution) override;
};

class Print : public Command
        {
        public:
            explicit Print(std::string &args);
            void command(ContextExecution &context_execution) override;
};

class Comment : public Command
        {
        public:
            explicit Comment(std::string &args);
            void command(ContextExecution &context_execution) override;
};

