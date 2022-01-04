//
// Created by bulga on 03.01.2022.
//
#include "StackCalculator.h"
#include <string>
#include <charconv>
#include <algorithm>

bool is_number(const std::string &s) {
    return !s.empty() && (std::all_of(s.begin(), s.end(), [](char c) { return ::isdigit(c); }) || (s[0] == '-' && std::all_of(s.begin() + 1, s.end(), [](char c) { return ::isdigit(c); })));
}

Pop::Pop(std::string &args) : Command(args) {}

void Pop::command(ContextExecution &context_execution)
{
    if (!context_execution.stack.empty()) context_execution.stack.pop();
    else throw PopException();
}

Push::Push(std::string &args) : Command(args) {}

void Push::command(ContextExecution &context_execution)
{
    if (is_number(params))
    {
        int64_t result;
        auto[ptr, ec]{std::from_chars(params.data(), params.data() + params.size(), result)};
        if (ec == std::errc::result_out_of_range) throw OverflowException();
        context_execution.stack.push(result);
    }
    else
        {
        auto elem = context_execution.variables.find(params);
        if (elem == context_execution.variables.end()) throw PushException();
        else context_execution.stack.push(elem->second);
    }
}


Peek::Peek(std::string &args) : Command(args) {}

void Peek::command(ContextExecution &context_execution) {
    if (!context_execution.stack.empty()) context_execution.variables[params] = context_execution.stack.top();
    else throw PeekException();
}


Abs::Abs(std::string &args) : Command(args) {}

void Abs::command(ContextExecution &context_execution)
{
    if (!context_execution.stack.empty())
    {
        SafeInt<int64_t, CustomException> val = context_execution.stack.top();
        context_execution.stack.pop();
        SafeInt<int64_t, CustomException> result = val;
        if (val < 0)  result = -val;
        context_execution.stack.push(result);
    }
    else throw AbsException();
}

Plus::Plus(std::string &args) : Command(args) {}

void Plus::command(ContextExecution &context_execution) {
    if (context_execution.stack.size() >= 2)
    {
        SafeInt<int64_t, CustomException> val1 = context_execution.stack.top();
        context_execution.stack.pop();
        SafeInt<int64_t, CustomException> val2 = context_execution.stack.top();
        context_execution.stack.pop();
        SafeInt<int64_t, CustomException> result = val1 + val2;
        context_execution.stack.push(result);
    }
    else throw NEElement();

}

Minus::Minus(std::string &args) : Command(args) {}

void Minus::command(ContextExecution &context_execution)
{
    if (context_execution.stack.size() >= 2)
    {
        SafeInt<int64_t, CustomException> val1 = context_execution.stack.top();
        context_execution.stack.pop();
        SafeInt<int64_t, CustomException> val2 = context_execution.stack.top();
        context_execution.stack.pop();
        SafeInt<int64_t, CustomException> result = val2 - val1;
        context_execution.stack.push(result);
    }
    else throw NEElement();
}

Multiply::Multiply(std::string &args) : Command(args) {}

void Multiply::command(ContextExecution &context_execution)
{
    if (context_execution.stack.size() >= 2)
    {
        SafeInt<int64_t, CustomException> val1 = context_execution.stack.top();
        context_execution.stack.pop();
        SafeInt<int64_t, CustomException> val2 = context_execution.stack.top();
        context_execution.stack.pop();
        SafeInt<int64_t, CustomException> result = val1 * val2;
        context_execution.stack.push(result);
    }
    else throw NEElement();

}

Division::Division(std::string &args) : Command(args) {}

void Division::command(ContextExecution &context_execution)
{
    if (context_execution.stack.size() >= 2)
    {
        int64_t val1 = context_execution.stack.top();
        context_execution.stack.pop();
        int64_t val2 = context_execution.stack.top();
        if (val1 != 0)
        {
            context_execution.stack.pop();
            int64_t res;
            SafeDivide(val2, val1, res);
            context_execution.stack.push(res);
        }
        else throw DivisionByZero();

    }
    else throw NEElement();
}

Print::Print(std::string &args) : Command(args) {}

void Print::command(ContextExecution &context_execution)
{
    if (!context_execution.stack.empty())
    {
        SafeInt<int64_t, CustomException> val = context_execution.stack.top();
        context_execution.variables["result"] = val;
        std::cout << (int64_t) val << std::endl;
    }
    else throw PrintException();
}

Read::Read(std::string &args) : Command(args) {}

void Read::command(ContextExecution &context_execution)
{
    std::string val;
    std::cin >> val;
    if (is_number(val))
    {
        int64_t result;
        std::from_chars(val.data(), val.data() + val.size(), result);
        context_execution.stack.push(result);
    }
    else throw ReadException();
}

Comment::Comment(std::string &args) : Command(args) {}

void Comment::command(ContextExecution &context_execution) {}

void CustomException::SafeIntOnOverflow()
{
    throw OverflowException();
}


