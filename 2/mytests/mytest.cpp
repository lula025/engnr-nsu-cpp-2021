//
// Created by bulga on 04.01.2022.
//

#include <fstream>
#include "../src/command/StackCalculator.h"
#include "gtest/gtest.h"

TEST(CALCULATOR1, EXAMPLE_TEST) {
std::stringstream data("# myVar = -14 / 5\n"
                       "PUSH -14\n"
                       "PUSH 5\n"
                       "DIV\n"
                       "PEEK myVar\n"
                       "POP\n"
                       "# PRINT (9 - myVar) * 20\n"
                       "PUSH 9\n"
                       "PUSH myVar\n"
                       "MINUS\n"
                       "PUSH 20\n"
                       "MUL\n"
                       "PRINT");
int64_t result = 220;
StackCalc stack;
stack = ReadFromStream(data);
EXPECT_EQ(stack.FindResult()["result"], result);
}

TEST(CALCULATOR1, EASY_TEST) {
    std::stringstream data("PUSH 1\n"
                           "PUSH 2\n"
                           "PUSH 3\n"
                           "PLUS\n"
                           "PLUS\n"
                           "PUSH 6\n"
                           "MINUS\n"
                           "PRINT");
    int64_t result = 0;
    StackCalc stack;
    stack = ReadFromStream(data);
    EXPECT_EQ(stack.FindResult()["result"], result);
}
TEST(CALCULATOR1, OVERFLOW_BY_DIV) {
    std::stringstream data("PUSH -9223372036854775808\n"
                           "PUSH -1\n"
                           "DIV\n"
                           "PRINT"
    );
    EXPECT_THROW(ReadFromStream(data), OverflowException);
}

TEST(CALCULATOR1, HARD_TEST) {
std::stringstream data("PUSH 4\n"
                       "PEEK a\n"
                       "POP\n"
                       "\n"
                       "PUSH 6\n"
                       "PEEK c\n"
                       "POP\n"
                       "\n"
                       "PUSH 2\n"
                       "PEEK d\n"
                       "POP\n"
                       "\n"
                       "PUSH 36\n"
                       "PEEK e\n"
                       "POP\n"
                       "\n"
                       "PUSH 11\n"
                       "PEEK f\n"
                       "POP\n"
                       "\n"
                       "PUSH 2\n"
                       "PEEK g\n"
                       "POP\n"
                       "\n"
                       "\n"
                       "PUSH a\n"
                       "PUSH c\n"
                       "\n"
                       "PLUS\n"
                       "\n"
                       "PUSH d\n"
                       "\n"
                       "MUL\n"
                       "\n"
                       "PUSH e\n"
                       "\n"
                       "PUSH f\n"
                       "PUSH g\n"
                       "\n"
                       "MINUS\n"
                       "\n"
                       "DIV\n"
                       "\n"
                       "MINUS\n"
                       "\n"
                       "PRINT");
int64_t result = 16;
StackCalc stack;
stack = ReadFromStream(data);
EXPECT_EQ(stack.FindResult()["result"], result);
}

TEST(CALCULATOR1, ERROR_TEST) {
std::stringstream data("PUSH 1\n"
                       "PUSH 5\n"
                       "PLUS\n"
                       "POP\n"
                       "POP\n");
EXPECT_THROW(ReadFromStream(data), PopException);

}

TEST(CALCULATOR1, DIVISION_BY_ZERO) {
std::stringstream data("PUSH 1\n"
                       "PUSH 0\n"
                       "DIV\n");
EXPECT_THROW(ReadFromStream(data), DivisionByZero);

}

TEST(CALCULATOR1, UNKNOWN_COMMAND) {
std::stringstream data("PUSH 1\n"
                       "PUSH 2\n"
                       "PLUS\n"
                       "PRIN\n");
EXPECT_THROW(ReadFromStream(data), UnknownCommand);

}

TEST(CALCULATOR1, OVERFLOW_BY_PLUS) {
std::stringstream data("PUSH 9223372036854775806\n"
                       "PUSH 9223372036854775806\n"
                       "PLUS\n");
EXPECT_THROW(ReadFromStream(data), OverflowException);

}

TEST(CALCULATOR1, OVERFLOW_BY_ABS) {
std::stringstream data("PUSH -9223372036854775808\n"
                       "ABS\n");
EXPECT_THROW(ReadFromStream(data), OverflowException);
}
