#include "math_app.hpp"

/*
Math app
Usage: enter <num1> <operator> <num2> (be careful of spaces between each operator)
Supported operations: + - x /
Logging: logs are send through a messageQ to the logger
*/

int main(int argc, char *argv[])
{
    messageq_sender math_app_obj;               // math_app object of the class message queue sender
    math_app_obj.messageq_connect("/math_app"); // name of the app is used as queue name
    if (argc != 4)                              // check the number of arguments entered
    {
        cout << "Error: Format entered is invalid" << endl;
        cout << "Input format: " << argv[0] << " <num1> <operator> <num2>" << endl;
        LOG("MATH APP: User entered unsupported format.");
        return 1;
    }
    if (argc == 2 && strcmp(argv[1], "--help") == 0) // Application manual
    {
        print_help(argv[0]);                     // Help function implementation
        LOG("MATH APP: Help printed on screen"); // send a log through the queue
        return 0;
    }
    char operation = argv[2][0];                //Check if user is trying to divide by zero as it is undefined
    if (atof(argv[3]) == 0 && operation == '/')
    {
        cout << "Error:You can not divide by 0!" << endl;
        LOG("MATH APP: User tried to divide by 0, porgram terminated");
        return 1;
    }
    calculator math_app(atof(argv[1]), atof(argv[3])); // create object of the type math and pass it the numbers
    switch (operation)      //next part depends on which operation the user needs
    {
    case '+':           
        math_app.add();     //addition operation
        LOG("MATH APP: Addition operation is done.");
        break;
    case '-':
        math_app.sub();     //subtraction operation
        LOG("MATH APP: Subtraction operation is done.");
        break;
    case 'x':
        math_app.multiply();        //multiplication operation
        LOG("MATH APP: Multiplication operation is done.");
        break;
    case '/':
        math_app.divide();         //division operation
        break;
    default:        //If user entered any other opration
        cout << "Error: Invalid operation entered."<<endl;
        cout << "Supported operators: +, -, x, /" << endl;
        LOG("MATH APP: Error: Invalid operation entered.");
        return 1;
    }
    math_app.result_print();        //print the result 
    LOG("MATH APP: Result printed.");
    return 0;
}

/*
    function used to print application manual
*/
void print_help(char *argv)
{
    cout << "To use the math applicatoin:" << endl;
    cout << "Arguments format: " << argv[0] << " <num1> <operator> <num2>" << endl;
    cout << "Perform basic math operations based on the entered arguments." << endl;
    cout << "Supported operators: +, -, x, /" << endl;
}
