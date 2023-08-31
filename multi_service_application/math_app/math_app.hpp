
#ifndef MATH_APP_HPP
#define MATH_APP_HPP
#include <iostream>
#include <cstdlib>
#include "../ipc_lib/ipc_lib.hpp"
using namespace std;
#define LOG math_app_obj.messageq_send // macro used to send logs through MQ

class calculator
{
private:
    char operation;
    double num1;
    double num2;
    double result;

public:
    calculator(double num1, double num2)
    {
        this->num1 = num1;
        this->num2 = num2;
    }
    double add()
    {
        result = num1 + num2;
        return num1 + num2;
    }

    double sub()
    {
        result = num1 - num2;
        return num1 - num2;
    }

    double multiply()
    {
        result = num1 * num2;
        return num1 * num2;
    }

    double divide()
    {
        if (num2 == 0)
        {
            cout << "Error: Division by zero is not allowed.\n";
            return 0;
        }
        result = num1 / num2;
        return num1 / num2;
    }
    void result_print()
    {
        cout << "Result= " << result << "\n";
    }
};

void print_help(char* argv);
#endif