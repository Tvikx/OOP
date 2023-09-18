#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc != 3)
    {

        cerr << "Program is on the form: " << argv[0] << " <input_FileName.txt> <output_FileName.csv>\n";
        return 1;
    }

    ifstream file;
    file.open(argv[1]);

    if (!file)
    {
        cerr << "file is not open";
        return 1;
    }

    if (file.peek() == EOF)
    {
        cerr << "file is empty";
        return 1;
    }

    list<string> text;
    map<string, int> dictionary;
    map<string, int>::iterator it;

    string s;

    for (getline(file, s); !file.eof(); getline(file, s)) // last line dont read
    {
        text.push_back(s);
        for (int i = 0; i < s.length(); i++)
        {
            if (isdigit(s[i]) || isalpha(s[i]))
            {
                string temp;
                while (isdigit(s[i]) || isalpha(s[i]))
                {
                    temp.push_back(s[i]);
                    i++;
                }

                it = dictionary.find(temp);
                if (it == dictionary.end())
                    dictionary.insert(make_pair(temp, 1));
                else
                {
                    int a = it->second;
                    a++;
                    it->second = a;
                }
            }
        }
    }

    getline(file, s);
    text.push_back(s);
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]) || isalpha(s[i]))
        {
            string temp;
            while (isdigit(s[i]) || isalpha(s[i]))
            {
                temp.push_back(s[i]);
                i++;
            }

            it = dictionary.find(temp);
            if (it == dictionary.end())
                dictionary.insert(make_pair(temp, 1));
            else
            {
                int a = it->second;
                a++;
                it->second = a;
            }
        }
    }
    file.close();

    ofstream out;
    out.open(argv[2]);

    double all_occur = 0;
    it = dictionary.begin();
    for (it; it != dictionary.end(); ++it)
    {
        all_occur += (double)it->second;
    }

    map<string, int>::iterator it_max = dictionary.begin();

    while (!dictionary.empty())
    {
        it = dictionary.begin(), it_max = it;

        for (it; it != dictionary.end(); ++it)
        {
            if (it->second > it_max->second)
                it_max = it;
        }
        out << it_max->second << ',' << it_max->first << ',' << ((double)it_max->second / all_occur) << endl;
        dictionary.erase(it_max);

    }

    return 0;
}