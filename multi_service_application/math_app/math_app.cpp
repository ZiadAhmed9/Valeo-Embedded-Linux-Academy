#include <iostream>
#include <cstdlib>
#include "math_app.hpp"
#include "../ipc_lib/ipc_lib.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    messageq_sender math_app_obj;
    math_app_obj.messageq_connect("/math_app");
    if (argc == 2 && std::strcmp(argv[1], "--help") == 0)
    {
        std::cout << "Usage: " << argv[0] << " <num1> <operator> <num2>\n"
              << "Perform basic math operations based on the entered arguments.\n"
              << "Supported operators: +, -, *, /\n";
        return 0;
    }
    double num1 = atof(argv[1]);
    char op = argv[2][0];
    double num2 = atof(argv[3]);
    double result;
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <num1> <operator> <num2>\n";
        return 1;
    }
    switch (op)
    {
    case '+':
        result = add(num1, num2);
        math_app_obj.messageq_send("we preformed an addition op");
        break;
    case '-':
        result = sub(num1, num2);
        break;
    case 'x':
        result = multiply(num1, num2);
        break;
    case '/':
        if (num2 == 0)
        {
            cout << "Error: Division by zero is not allowed.\n";
            return 1;
        }
        result = divide(num1, num2);
        break;
    default:
        cout << "Error: Invalid operator.\n";
        return 1;
    }

    cout << "Result= " << result << "\n";
    return 0;
}


double add(double num1,double num2)
{
    return num1+num2;
}

double sub(double num1,double num2)
{
    return num1-num2;
}

double multiply(double num1,double num2)
{
    return num1*num2;
}

double divide(double num1,double num2)
{
    return num1/num2;
}