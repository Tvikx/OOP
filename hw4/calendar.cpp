#include "calendar.hpp"


Calendar::Calendar()
{
    for (int i = 0; i < 36524; i++)
        arr[i] = 0;
}
void Calendar::write_inc(int dat1, int dat2, int inc)
{
    inc = inc / (dat2 - dat1 + 1);
    for (int i = dat1; i <= dat2; i++)
        arr[i] += inc;
}
int Calendar::calc_inc(int dat1, int dat2)
{
    int res = 0;
    for (int i = dat1; i <= dat2; i++)
        res += arr[i];

    return res;
}

Dates::Dates(tm date1, tm date2)
{
    tm year_2000 = {0, 0, 0, 1, 0, 100};
    sec_2000 = mktime(&year_2000);
    data1.tp = &date1;
    data2.tp = &date2;
    data1.sec = mktime(data1.tp);
    data2.sec = mktime(data2.tp);
}
int Dates::calc_pos_dat1()
{
    int res = (difftime(data1.sec, sec_2000) / 3600) / 24;
    return res;
}
int Dates::calc_pos_dat2()
{
    int res = (difftime(data2.sec, sec_2000) / 3600) / 24;
    return res;
}

istream& operator>>(istream& in, tm& dat)
{
    int year, month, day;
    in >> year;
    dat.tm_year = year - 1900;
    in.ignore(1);
    in >> month;
    dat.tm_mon = month - 1;
    in.ignore(1);
    in >> day;
    dat.tm_mday = day;
    dat.tm_hour = 0;
    dat.tm_min = 0;
    dat.tm_sec = 0;
    return in;
}
