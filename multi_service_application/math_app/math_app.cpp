#include "math_app.hpp"

/*
Math app
Usage: enter <num1> <operator> <num2> (be careful of spaces between each operator)
Supported operations: + - x /
Logging: logs are send through a messageQ to the logger
*/

int main(int argc, char *argv[])
{
    messageq_sender math_app_obj;
    math_app_obj.messageq_connect("/math_app");
    if (argc == 2 && std::strcmp(argv[1], "--help") == 0)
    {
        print_help(argv[0]);
        LOG("MATH APP: Help printed on screen");
        return 0;
    }
    calculator math_app(atof(argv[1]), atof(argv[3]));
    char op = argv[2][0];
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <num1> <operator> <num2>\n";
        LOG("MATH APP: Invalid arguments entered.");
        return 1;
    }
    switch (op)
    {
    case '+':
        math_app.add();
        LOG("MATH APP: Addition operation is done.");
        break;
    case '-':
        math_app.sub();
        LOG("MATH APP: Subtraction operation is done.");
        break;
    case 'x':
        math_app.multiply();
        LOG("MATH APP: Multiplication operation is done.");
        break;
    case '/':
        math_app.divide();
        break;
    default:
        cout << "MATH APP: Error: Invalid operator.\n";
        LOG("MATH APP: Error: Invalid operator.");
        return 1;
    }
    math_app.result_print();
    LOG("MATH APP: Result printed.");
    return 0;
}

void print_help(char *argv)
{
    std::cout << "Usage: " << argv[0] << " <num1> <operator> <num2>\n"
              << "Perform basic math operations based on the entered arguments.\n"
              << "Supported operators: +, -, x, /\n";
}