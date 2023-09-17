#include <iostream>
#include <regex>
#include <stack>

using namespace std;

void argCheck(int argc, string s);
string characterCheck(string s);
string deleteDashes(string s);
string deleteSpaces(string s);
string changeCode(string s);
string bracketsProcessing(string s);

int main(int argc, char *argv[]) {

    argCheck(argc, argv[0]);
    string num; 

    try
    {
        num = characterCheck(argv[1]);
        num = deleteDashes(num);
        num = deleteSpaces(num);
        num = changeCode(num);
        num = bracketsProcessing(num);
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
        exit(1);
    }

    cout << num << endl;

    return 0;
}

    /*checking the correctness of the command call*/
void argCheck(int argc, string s)
{
    if (argc != 2)
        throw "inccorect program call";
}

    /*checking the correctness of the characters in the number*/
string characterCheck(string s)
{
    const regex r(R"(^(\+7|8)([0-9]|\s|-|\(|\))*([0-9|\)]$))");

    if (regex_match(s, r))
        return s;
    throw "inccorect characters in number";
}

    /*deletes dashes fromm number*/
string deleteDashes(string s)
{
    size_t found;
    while ((found = s.find('-')) != s.npos)
    {
        int temp = found + 1;

        if (s[temp] == '-')
            throw "inccorect dashes in number";
        else
            s.erase(found, 1);
    }
    return s;
}

    /*deletes spaces from number*/
string deleteSpaces(string s)
{
    size_t found;
    while ((found = s.find(' ')) != s.npos)
    {
        s.erase(found, 1);
    }
    return s;
}

    /*changes the country code to +7*/
string changeCode(string s)
{
    if (s[0] == '8')
    {
        s.erase(0, 1);
        s = "+7" + s;
    }
    return s;
}

    /*processing brackets in number*/
string bracketsProcessing(string s)
{

    stack<char> st;
    int count = 0;

    int i = 0;

    while (i != s.size())
    {
        if (s[i] == '(')
        {
            st.push(s[i]);
            count++;
            s.erase(i, 1);
            continue;
        }
        if (s[i] == ')')
        {
            if (st.empty())
            {
                throw "inccorect brackets in number";
            }
            st.pop();
            s.erase(i, 1);
            continue;
        }
        i++;
    }

    if ((!st.empty()) || (count > 1))
    {
        throw "inccorect brackets in number";
    }

    return s;
}