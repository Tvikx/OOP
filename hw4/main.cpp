#include "calendar.hpp"


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int q;
    if (!in.is_open())
        throw runtime_error("No file");
    in >> q;
    Calendar c;
    for (int i = 0; i < q; i++)
    {
        string request;
        char letter;
        while (in.get(letter)){
            if(letter == '\n') continue;
            if(letter == ' ') break;
            request.push_back(letter);
        }
        tm tp1, tp2;
        in >> tp1;
        in >> tp2;

        Dates d(tp1, tp2);
        if (request == "Earn")
        {
            int income;
            in >> income;
            c.write_inc(d.calc_pos_dat1(), d.calc_pos_dat2(), income);
        }
        else
        {
            int inc = c.calc_inc(d.calc_pos_dat1(), d.calc_pos_dat2());
            out << inc << endl;
        }
    }
    in.close();
    out.close();
    
    return 0;
}

