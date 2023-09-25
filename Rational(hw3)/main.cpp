#include "beest_headee_ever.h"

int main()
{
    string input;
    getline(cin, input);
    stringstream ss(input);
    Rational r1, r2;
    char operation;
    try
    {
        ss >> r1;
        ss.ignore(1);
        ss >> operation;
        ss.ignore(1);
        ss >> r2;
    }
    catch (exception &ex)
    {
        std::cout << "Invalid argument" << std::endl;
        return 1;
    }
    Rational res;
    try
    {
        switch (operation)
        {
        case '+':
        {
            res = r1 + r2;
            break;
        }
        case '-':
        {
            res = r1 - r2;
            break;
        }
        case '*':
        {
            res = r1 * r2;
            break;
        }
        case '/':
        {
            res = r1 / r2;
            break;
        }
        default:
        {
            std::cout << "Invalid operation" << std::endl;
        }
        }
    }
    catch (exception &ex)
    {
        std::cout << "Division by zero" << std::endl;
        return 2;
    }
    cout << res;
    return 0;
}
