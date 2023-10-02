#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

    
typedef struct Data_t
{
    tm* tp;
    time_t sec;
}Data;

class Calendar
{
public:
    Calendar();
    void write_inc(int dat1, int dat2, int inc);
    int calc_inc(int dat1, int dat2);
private:
    int arr[36524];
};

class Dates
{
public:
    Dates(tm date1, tm date2);
    int calc_pos_dat1();
    int calc_pos_dat2();
private:
    Data data1;
    Data data2;
    time_t sec_2000;
};

istream& operator>>(istream& in, tm& dat);